#include "Renderer_if.h"
#include "spg.h"
#include "cheats.h"
#include "hw/_vmem.h"
#include "hw/pvr/pvr_mem.h"
#include "oslib/oslib.h"
#include "rend/TexCache.h"
#include "cfg/option.h"

#include <mutex>
#include <zlib.h>

u32 VertexCount=0;
u32 FrameCount=1;

Renderer* renderer;
static Renderer* fallback_renderer;

cResetEvent rs, re;
static bool do_swap;
std::mutex swap_mutex;
u32 fb_w_cur = 1;

// direct framebuffer write detection
static bool render_called = false;
u32 fb_watch_addr_start;
u32 fb_watch_addr_end;
bool fb_dirty;

bool pend_rend = false;

TA_context* _pvrrc;

static void dump_frame(const char* file, TA_context* ctx, u8* vram, const u8* vram_ref = NULL) {
	FILE* fw = fopen(file, "wb");

	//append to it
	fseek(fw, 0, SEEK_END);

	u32 bytes = ctx->tad.End() - ctx->tad.thd_root;

	fwrite("TAFRAME4", 1, 8, fw);

	fwrite(&ctx->rend.isRTT, 1, sizeof(ctx->rend.isRTT), fw);
	u32 zero = 0;
	fwrite(&zero, 1, sizeof(bool), fw);	// Was autosort
	fwrite(&ctx->rend.fb_X_CLIP.full, 1, sizeof(ctx->rend.fb_X_CLIP.full), fw);
	fwrite(&ctx->rend.fb_Y_CLIP.full, 1, sizeof(ctx->rend.fb_Y_CLIP.full), fw);

	fwrite(ctx->rend.global_param_op.head(), 1, sizeof(PolyParam), fw);
	fwrite(ctx->rend.verts.head(), 1, 4 * sizeof(Vertex), fw);

	u32 t = VRAM_SIZE;
	fwrite(&t, 1, sizeof(t), fw);
	
	u8* compressed;
	uLongf compressed_size;
	u8* src_vram = vram;

	if (vram_ref) {
		src_vram = (u8*)malloc(VRAM_SIZE);

		for (u32 i = 0; i < VRAM_SIZE; i++) {
			src_vram[i] = vram[i] ^ vram_ref[i];
		}
	}

	compressed = (u8*)malloc(VRAM_SIZE+16);
	compressed_size = VRAM_SIZE;
	verify(compress(compressed, &compressed_size, src_vram, VRAM_SIZE) == Z_OK);
	fwrite(&compressed_size, 1, sizeof(compressed_size), fw);
	fwrite(compressed, 1, compressed_size, fw);
	free(compressed);

	if (src_vram != vram)
		free(src_vram);

	fwrite(&bytes, 1, sizeof(t), fw);
	compressed = (u8*)malloc(bytes + 16);
	compressed_size = VRAM_SIZE;
	verify(compress(compressed, &compressed_size, ctx->tad.thd_root, bytes) == Z_OK);
	fwrite(&compressed_size, 1, sizeof(compressed_size), fw);
	fwrite(compressed, 1, compressed_size, fw);
	free(compressed);

	fwrite(&ctx->tad.render_pass_count, 1, sizeof(u32), fw);
	for (u32 i = 0; i < ctx->tad.render_pass_count; i++) {
		u32 offset = ctx->tad.render_passes[i] - ctx->tad.thd_root;
		fwrite(&offset, 1, sizeof(offset), fw);
	}

	fwrite(pvr_regs, 1, sizeof(pvr_regs), fw);

	fclose(fw);
}

TA_context* read_frame(const char* file, u8* vram_ref = NULL) {
	
	FILE* fw = fopen(file, "rb");
	if (fw == NULL)
		die("Cannot open frame to display");
	char id0[8] = { 0 };
	u32 t = 0;

	if (fread(id0, 1, 8, fw) != 8) {
		fclose(fw);
		return 0;
	}

	if (memcmp(id0, "TAFRAME", 7) != 0 || (id0[7] != '3' && id0[7] != '4')) {
		fclose(fw);
		return 0;
	}
	u32 sizeofPolyParam = sizeof(PolyParam);
	u32 sizeofVertex = sizeof(Vertex);
	if (id0[7] == '3')
	{
		sizeofPolyParam -= 12;
		sizeofVertex -= 16;
	}

	TA_context* ctx = tactx_Alloc();

	ctx->Reset();

	ctx->tad.Clear();

	verify(fread(&ctx->rend.isRTT, 1, sizeof(ctx->rend.isRTT), fw) == sizeof(ctx->rend.isRTT));
	verify(fread(&t, 1, sizeof(bool), fw) == sizeof(bool));	// Was autosort
	verify(fread(&ctx->rend.fb_X_CLIP.full, 1, sizeof(ctx->rend.fb_X_CLIP.full), fw) == sizeof(ctx->rend.fb_X_CLIP.full));
	verify(fread(&ctx->rend.fb_Y_CLIP.full, 1, sizeof(ctx->rend.fb_Y_CLIP.full), fw) == sizeof(ctx->rend.fb_Y_CLIP.full));

	verify(fread(ctx->rend.global_param_op.Append(), 1, sizeofPolyParam, fw) == sizeofPolyParam);
	Vertex *vtx = ctx->rend.verts.Append(4);
	for (int i = 0; i < 4; i++)
		verify(fread(vtx + i, 1, sizeofVertex, fw) == sizeofVertex);

	verify(fread(&t, 1, sizeof(t), fw) == sizeof(t));
	verify(t == VRAM_SIZE);

	_vmem_unprotect_vram(0, VRAM_SIZE);

	uLongf compressed_size;

	verify(fread(&compressed_size, 1, sizeof(compressed_size), fw) == sizeof(compressed_size));

	u8* gz_stream = (u8*)malloc(compressed_size);
	verify(fread(gz_stream, 1, compressed_size, fw) == compressed_size);
	uLongf tl = t;
	verify(uncompress(vram.data, &tl, gz_stream, compressed_size) == Z_OK);
	free(gz_stream);

	verify(fread(&t, 1, sizeof(t), fw) == sizeof(t));
	verify(fread(&compressed_size, 1, sizeof(compressed_size), fw) == sizeof(compressed_size));
	gz_stream = (u8*)malloc(compressed_size);
	verify(fread(gz_stream, 1, compressed_size, fw) == compressed_size);
	tl = t;
	verify(uncompress(ctx->tad.thd_data, &tl, gz_stream, compressed_size) == Z_OK);
	free(gz_stream);

	ctx->tad.thd_data += t;

	if (fread(&t, 1, sizeof(t), fw) > 0) {
		ctx->tad.render_pass_count = t;
		for (u32 i = 0; i < t; i++) {
			u32 offset;
			verify(fread(&offset, 1, sizeof(offset), fw) == sizeof(offset));
			ctx->tad.render_passes[i] = ctx->tad.thd_root + offset;
		}
	}
	verify(fread(pvr_regs, 1, sizeof(pvr_regs), fw) == sizeof(pvr_regs));

	fclose(fw);
    
    return ctx;
}

bool dump_frame_switch = false;

static bool rend_frame(TA_context* ctx)
{
	if (dump_frame_switch) {
		char name[32];
		sprintf(name, "dcframe-%d", FrameCount);
		dump_frame(name, _pvrrc, &vram[0]);
		dump_frame_switch = false;
	}
	bool proc = renderer->Process(ctx);

	if (!proc || (!ctx->rend.isRTT && !ctx->rend.isRenderFramebuffer))
		// If rendering to texture, continue locking until the frame is rendered
		re.Set();

	return proc && renderer->Render();
}

bool rend_single_frame(const bool& enabled)
{
	do
	{
		if (!rs.Wait(50))
			return false;
		if (do_swap)
		{
			do_swap = false;
			if (renderer->Present())
			{
				rs.Set(); // don't miss any render
				return true;
			}
		}
		if (!enabled)
			return false;

		_pvrrc = DequeueRender();
	}
	while (!_pvrrc);

	bool frame_rendered = rend_frame(_pvrrc);

	if (frame_rendered)
	{
		{
			std::lock_guard<std::mutex> lock(swap_mutex);
			if (config::DelayFrameSwapping && !_pvrrc->rend.isRenderFramebuffer && fb_w_cur != FB_R_SOF1 && !do_swap)
				// Delay swap
				frame_rendered = false;
			else
				// Swap now
				do_swap = false;
		}
		if (frame_rendered)
			frame_rendered = renderer->Present();
	}

	if (_pvrrc->rend.isRTT)
		re.Set();

	//clear up & free data ..
	FinishRender(_pvrrc);
	_pvrrc = nullptr;

	return frame_rendered;
}

Renderer* rend_GLES2();
Renderer* rend_GL4();
Renderer* rend_norend();
Renderer* rend_Vulkan();
Renderer* rend_OITVulkan();

static void rend_create_renderer()
{
#ifdef NO_REND
	renderer	 = rend_norend();
#else
	switch (config::RendererType)
	{
	default:
	case RenderType::OpenGL:
         renderer = rend_GLES2();
         break;
#if defined(GLES) && !defined(__APPLE__)
	case RenderType::OpenGL_OIT:
         renderer = rend_GL4();
         fallback_renderer = rend_GLES2();
         break;
#endif
#ifdef USE_VULKAN
	case RenderType::Vulkan:
		renderer = rend_Vulkan();
		break;
	case RenderType::Vulkan_OIT:
		renderer = rend_OITVulkan();
		break;
#endif
/*	default:
         renderer = rend_norend();
         break;
*/
	}
#endif
}

void rend_init_renderer()
{
	if (renderer == NULL)
		rend_create_renderer();
	if (!renderer->Init())
    {
		delete renderer;
    	if (fallback_renderer == NULL || !fallback_renderer->Init())
    	{
            delete fallback_renderer;
    		die("Renderer initialization failed\n");
    	}
    	INFO_LOG(PVR, "Selected renderer initialization failed. Falling back to default renderer.");
    	renderer  = fallback_renderer;
    	fallback_renderer = NULL;	// avoid double-free
    }
}

void rend_term_renderer()
{
	if (renderer != NULL)
	{
		renderer->Term();
		delete renderer;
		renderer = NULL;
	}
	if (fallback_renderer != NULL)
	{
		delete fallback_renderer;
		fallback_renderer = NULL;
	}
}

void rend_reset()
{
	FinishRender(DequeueRender());
	do_swap = false;
	render_called = false;
	pend_rend = false;
	FrameCount = 1;
	VertexCount = 0;
	fb_w_cur = 1;
}

void rend_start_render()
{
	render_called = true;
	pend_rend = false;
	TA_context* ctx = tactx_Pop(CORE_CURRENT_CTX);

	// No end of render interrupt when rendering the framebuffer
	if (!ctx || !ctx->rend.isRenderFramebuffer)
		SetREP(ctx);

	if (ctx)
	{
		if (ctx->rend.isRenderFramebuffer)
		{
			ctx->rend.isRTT = false;
			ctx->rend.fb_X_CLIP.min = 0;
			ctx->rend.fb_X_CLIP.max = 639;
			ctx->rend.fb_Y_CLIP.min = 0;
			ctx->rend.fb_Y_CLIP.max = 479;

			ctx->rend.fog_clamp_min = 0;
			ctx->rend.fog_clamp_max = 0xffffffff;
		}
		else
		{
			FillBGP(ctx);

			ctx->rend.isRTT = (FB_W_SOF1 & 0x1000000) != 0;

			ctx->rend.fb_X_CLIP = FB_X_CLIP;
			ctx->rend.fb_Y_CLIP = FB_Y_CLIP;

			ctx->rend.fog_clamp_min = FOG_CLAMP_MIN;
			ctx->rend.fog_clamp_max = FOG_CLAMP_MAX;
		}

		if (QueueRender(ctx))
		{
			palette_update();
			rs.Set();
			pend_rend = true;
		}
	}
}

void rend_end_render()
{
	if (pend_rend)
		re.Wait();
}

void rend_vblank()
{
	if (!render_called && fb_dirty && FB_R_CTRL.fb_enable)
	{
		DEBUG_LOG(PVR, "Direct framebuffer write detected");
		u32 saved_ctx_addr = PARAM_BASE;
		bool restore_ctx = ta_ctx != NULL;
		PARAM_BASE = 0xF00000;
		SetCurrentTARC(CORE_CURRENT_CTX);
		ta_ctx->Reset();
		ta_ctx->rend.isRenderFramebuffer = true;
		rend_start_render();
		PARAM_BASE = saved_ctx_addr;
		if (restore_ctx)
			SetCurrentTARC(CORE_CURRENT_CTX);
		fb_dirty = false;
	}
	render_called = false;
	check_framebuffer_write();
	cheatManager.apply();
}

void check_framebuffer_write()
{
	u32 fb_size = (FB_R_SIZE.fb_y_size + 1) * (FB_R_SIZE.fb_x_size + FB_R_SIZE.fb_modulus) * 4;
	fb_watch_addr_start = (SPG_CONTROL.interlace ? FB_R_SOF2 : FB_R_SOF1) & VRAM_MASK;
	fb_watch_addr_end = fb_watch_addr_start + fb_size;
}

void rend_cancel_emu_wait()
{
	FinishRender(NULL);
	re.Set();
}

void rend_set_fb_write_addr(u32 fb_w_sof1)
{
	if (fb_w_sof1 & 0x1000000)
		// render to texture
		return;
	fb_w_cur = fb_w_sof1;
}

void rend_swap_frame(u32 fb_r_sof1)
{
	std::lock_guard<std::mutex> lock(swap_mutex);
	if (fb_r_sof1 == fb_w_cur)
	{
		do_swap = true;
		rs.Set();
	}
}

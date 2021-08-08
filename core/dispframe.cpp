#include "cfg/cfg.h"
#include "rend/TexCache.h"
#include "emulator.h"

#include <csignal>

extern cResetEvent rs;
extern cResetEvent frame_finished;
extern TA_context* rqueue;

void SetREP(TA_context* cntx);
TA_context* read_frame(const char* file, u8* vram_ref = NULL);
void rend_set_fb_scale(float x,float y);

#ifdef TARGET_DISPFRAME
void *dc_run(void*)
{
	struct sigaction act, segv_oact;
	memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask);
    act.sa_sigaction = SIG_IGN;
    sigaction(SIGUSR1, &act, &segv_oact);

//    rend_set_fb_scale(1.0, 1.0);
 fb_scale_x = fb_scale_y = 1.0;

    char frame_path[512];
    std::string s = cfgLoadStr("config", "image", "null");
    strcpy(frame_path, s.c_str());

    printf("Loading %s\n", frame_path);

	double t0 = os_GetSeconds();
	TA_context*ctx = read_frame(frame_path);
	ctx->rend.fog_clamp_min = FOG_CLAMP_MIN;
	ctx->rend.fog_clamp_max = FOG_CLAMP_MAX;
	double t1 = os_GetSeconds();
	fog_needs_update = true;
	pal_needs_update = true;
	printf("Loaded context in %g ms\n", (t1 - t0) * 1000);

	while(renderer_enabled)
	{
		tad_context saved_tad = ctx->tad;
		rend_context saved_rend = ctx->rend;
		FillBGP(ctx);

		if (rqueue)
			frame_finished.Wait();
		if (QueueRender(ctx))  {
			palette_update();
			rs.Set();
		}
		else
			SetREP(NULL);	// Sched end of render interrupt
		ctx = tactx_Alloc();
		ctx->tad = saved_tad;
		ctx->rend = saved_rend;

		os_DoEvents();
	}
	return nullptr;
}
#endif

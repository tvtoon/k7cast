#pragma once
#include "oslib/oslib.h"
#include "hw/pvr/Renderer_if.h"
#include "cfg/option.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <memory>
#include <unordered_map>

//extern u8* vq_codebook;
extern u32 palette_index;
//extern u32 palette16_ram[1024];
extern u32 palette32_ram[1024];
extern bool pal_needs_update,fog_needs_update;
//extern u32 pal_hash_256[4];
//extern u32 pal_hash_16[64];
extern bool KillTex;
extern bool palette_updated;
//extern u32 detwiddle[2][11][1024];

template<class pixel_type>
class PixelBuffer
{
	pixel_type* p_buffer_start = nullptr;
	pixel_type* p_current_mipmap = nullptr;
	pixel_type* p_current_line = nullptr;
	pixel_type* p_current_pixel = nullptr;

	u32 pixels_per_line = 0;

public:
	~PixelBuffer()
	{
		deinit();
	}

	void init(u32 width, u32 height, bool mipmapped)
	{
		deinit();
		size_t size = width * height * sizeof(pixel_type);
		if (mipmapped)
		{
			do
			{
				width /= 2;
				height /= 2;
				size += width * height * sizeof(pixel_type);
			}
			while (width != 0 && height != 0);
		}
		p_buffer_start = p_current_line = p_current_pixel = p_current_mipmap = (pixel_type *)malloc(size);
		this->pixels_per_line = 1;
	}

	void init(u32 width, u32 height)
	{
		deinit();
		p_buffer_start = p_current_line = p_current_pixel = p_current_mipmap = (pixel_type *)malloc(width * height * sizeof(pixel_type));
		this->pixels_per_line = width;
	}

	void deinit()
	{
		if (p_buffer_start != NULL)
		{
			free(p_buffer_start);
			p_buffer_start = p_current_mipmap = p_current_line = p_current_pixel = NULL;
		}
	}

	void steal_data(PixelBuffer &buffer)
	{
		deinit();
		p_buffer_start = p_current_mipmap = p_current_line = p_current_pixel = buffer.p_buffer_start;
		pixels_per_line = buffer.pixels_per_line;
		buffer.p_buffer_start = buffer.p_current_mipmap = buffer.p_current_line = buffer.p_current_pixel = NULL;
	}

	void set_mipmap(int level)
	{
		size_t offset = 0;
		for (int i = 0; i < level; i++)
			offset += (1 << (2 * i));
		p_current_mipmap = p_current_line = p_current_pixel = p_buffer_start + offset;
		pixels_per_line = 1 << level;
	}

	__forceinline pixel_type *data(u32 x = 0, u32 y = 0)
	{
		return p_current_mipmap + pixels_per_line * y + x;
	}

	__forceinline void prel(u32 x, pixel_type value)
	{
		p_current_pixel[x] = value;
	}

	__forceinline void prel(u32 x, u32 y, pixel_type value)
	{
		p_current_pixel[y * pixels_per_line + x] = value;
	}

	__forceinline void rmovex(u32 value)
	{
		p_current_pixel += value;
	}
	__forceinline void rmovey(u32 value)
	{
		p_current_line += pixels_per_line * value;
		p_current_pixel = p_current_line;
	}
	__forceinline void amove(u32 x_m, u32 y_m)
	{
		//p_current_pixel=p_buffer_start;
		p_current_line = p_current_mipmap + pixels_per_line * y_m;
		p_current_pixel = p_current_line + x_m;
	}
};

void palette_update();

struct vram_block
{
	u32 start;
	u32 end;
	u32 len;
	u32 type;

	void* userdata;
};

class BaseTextureCacheData;

bool VramLockedWriteOffset(size_t offset);
void libCore_vramlock_Unlock_block(vram_block *block);
void libCore_vramlock_Lock(u32 start_offset, u32 end_offset, BaseTextureCacheData *texture);

void UpscalexBRZ(int factor, u32* source, u32* dest, int width, int height, bool has_alpha);

enum class TextureType { _565, _5551, _4444, _8888, _8 };

class BaseTextureCacheData
{
public:
//dreamcast texture parameters
	TSP tsp;
	TCW tcw;
// Decoded/filtered texture format
	TextureType tex_type;
//pixel data start address in vram (might be offset for mipmaps/etc)
	u32 sa;
//texture data start address in vram
	u32 sa_tex;
//width & height of the texture
	u32 texwidth, texheight;
//size, in bytes, in vram
	u32 size;
/*
	const PvrTexInfo* tex;
	TexConvFP *texconv;
	TexConvFP32 *texconv32;
	TexConvFP8 *texconv8;

Original type, because the caching is weird.
*/
 TextureType org_type;
 unsigned char bitdepth;
 unsigned char isplanar;
 unsigned char texconv;
 unsigned char texconv32;
 unsigned char texconv8;

 u32 dirty;
 vram_block* lock_block;
 u32 Updates;
 u32 palette_index;
//used for palette updates
 u32 palette_hash;			// Palette hash at time of last update
 u32 vq_codebook;            // VQ quantizers table for compressed textures
 u32 texture_hash;			// xxhash of texture data, used for custom textures
 u32 old_texture_hash;		// legacy hash
 u8* custom_image_data;		// loaded custom image data
 u32 custom_width;
 u32 custom_height;
 std::atomic_int custom_load_in_progress;

 void PrintTextureName();
 virtual std::string GetId() = 0;
 bool IsPaletted();
 bool IsMipmapped();
 const char* GetPixelFormatName();
 bool IsCustomTextureAvailable();
 void Create();
 void ComputeHash();
 void Update();
 virtual void UploadToGPU(int width, int height, u8 *temp_tex_buffer, bool mipmapped, bool mipmapsIncluded = false) = 0;
// virtual bool Force32BitTexture(TextureType type) const { return false; }
 virtual bool Force32BitTexture(TextureType type) const;
 void CheckCustomTexture();
//true if : dirty or paletted texture and hashes don't match
 bool NeedsUpdate();
 virtual bool Delete();
 virtual ~BaseTextureCacheData() = default;
// bool IsGpuHandledPaletted(TSP tsp, TCW tcw);
};

bool IsGpuHandledPaletted( const TSP tsp, const TCW tcw );

template<typename Texture>
class BaseTextureCache
{
 using TexCacheIter = typename std::unordered_map<u64, Texture>::iterator;
public:
 Texture *getTextureCacheData(TSP tsp, TCW tcw)
{
 u64 key = tsp.full & TSPTextureCacheMask.full;

// Paletted textures have a palette selection that must be part of the key
// We also add the palette type to the key to avoid thrashing the cache
// when the palette type is changed. If the palette type is changed back in the future,
// this texture will stil be available.
// if ((tcw.PixelFmt == PixelPal4 || tcw.PixelFmt == PixelPal8) && !BaseTextureCacheData::IsGpuHandledPaletted(tsp, tcw))
 if ((tcw.PixelFmt == PixelPal4 || tcw.PixelFmt == PixelPal8) && !IsGpuHandledPaletted(tsp, tcw))
  key |= ((u64)tcw.full << 32) | ((PAL_RAM_CTRL & 3) << 6) | ((tsp.FilterMode != 0) << 8);
 else
  key |= (u64)(tcw.full & TCWTextureCacheMask.full) << 32;

 TexCacheIter it = cache.find(key);
 Texture* texture;

 if (it != cache.end())
{
  texture = &it->second;
// Needed if the texture is updated
  texture->tcw.StrideSel = tcw.StrideSel;
}
//create if not existing
 else
{
  texture = &cache[key];
  texture->tsp = tsp;
  texture->tcw = tcw;
}

 return texture;
}

 void CollectCleanup()
{
 std::vector<u64> list;
 u32 TargetFrame = std::max((u32)120, FrameCount) - 120;

 for (const auto& pair : cache)
{
  if (pair.second.dirty && pair.second.dirty < TargetFrame) list.push_back(pair.first);

  if (list.size() > 5) break;
}

 for (u64 id : list)
{
  if (cache[id].Delete()) cache.erase(id);
}

}

 void Clear()
{
 for (auto& pair : cache) pair.second.Delete();

 cache.clear();
 KillTex = false;
 INFO_LOG(RENDERER, "Texture cache cleared");
}

protected:
 std::unordered_map<u64, Texture> cache;
// Only use TexU and TexV from TSP in the cache key
//     TexV : 7, TexU : 7
 const TSP TSPTextureCacheMask = { { 7, 7 } };
//     TexAddr : 0x1FFFFF, Reserved : 0, StrideSel : 0, ScanOrder : 1, PixelFmt : 7, VQ_Comp : 1, MipMapped : 1
 const TCW TCWTextureCacheMask = { { 0x1FFFFF, 0, 0, 1, 7, 1, 1 } };
};

void ReadFramebuffer(PixelBuffer<u32>& pb, int& width, int& height);
void WriteTextureToVRam(u32 width, u32 height, u8 *data, u16 *dst, u32 fb_w_ctrl = -1, u32 linestride = -1);
void MakeFogTexture(u8 *tex_data);
void dump_screenshot(u8 *buffer, u32 width, u32 height, bool alpha = false, u32 rowPitch = 0, bool invertY = true);

extern const std::array<f32, 16> D_Adjust_LoD_Bias;
//#undef clamp

extern float fb_scale_x, fb_scale_y;
/*
static inline void rend_set_fb_scale(float x, float y)
{
	fb_scale_x = x;
	fb_scale_y = y;
}
*/

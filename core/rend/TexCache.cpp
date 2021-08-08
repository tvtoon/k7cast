#include "TexCache.h"
#include "CustomTexture.h"
#include "deps/xbrz/xbrz.h"
#include "hw/pvr/pvr_mem.h"
#include "hw/_vmem.h"
#include "hw/sh4/mmu.h"

#include <algorithm>
#include <mutex>
#include <xxhash/xxhash.h>

#ifndef TARGET_NO_OPENMP
#include <omp.h>
#endif

/*
Exported from the header...
*/
//Planar
#define tex565_PL texture_PL<conv565_PL, u16>
#define tex1555_PL texture_PL<conv1555_PL, u16>
#define tex4444_PL texture_PL<conv4444_PL, u16>
#define texYUV422_PL texture_PL<convYUV_PL, u32>
#define texBMP_PL tex4444_PL

#define tex565_PL32 texture_PL<conv565_PL32, u32>
#define tex1555_PL32 texture_PL<conv1555_PL32, u32>
#define tex4444_PL32 texture_PL<conv4444_PL32, u32>

//Twiddle
#define tex565_TW texture_TW<conv565_TW, u16>
#define tex1555_TW texture_TW<conv1555_TW, u16>
#define tex4444_TW texture_TW<conv4444_TW, u16>
#define texYUV422_TW texture_TW<convYUV_TW, u32>
#define texBMP_TW tex4444_TW

#define tex565_TW32 texture_TW<conv565_TW32, u32>
#define tex1555_TW32 texture_TW<conv1555_TW32, u32>
#define tex4444_TW32 texture_TW<conv4444_TW32, u32>

//VQ
#define tex565_VQ texture_VQ<conv565_TW, u16>
#define tex1555_VQ texture_VQ<conv1555_TW, u16>
#define tex4444_VQ texture_VQ<conv4444_TW, u16>
#define texYUV422_VQ texture_VQ<convYUV_TW, u32>
#define texBMP_VQ tex4444_VQ
// According to the documentation, a texture cannot be compressed and use
// a palette at the same time. However the hardware displays them
// just fine.
#define tex565_VQ32 texture_VQ<conv565_TW32, u32>
#define tex1555_VQ32 texture_VQ<conv1555_TW32, u32>
#define tex4444_VQ32 texture_VQ<conv4444_TW32, u32>
/* Template bitching... */
#define texPAL4_TW texture_TW<convPAL4_TW<u16>, u16>
#define texPAL8_TW texture_TW<convPAL8_TW<u16>, u16>
#define texPAL4_TW32 texture_TW<convPAL4_TW<u32>, u32>
#define texPAL8_TW32  texture_TW<convPAL8_TW<u32>, u32>
#define texPAL4PT_TW texture_TW<convPAL4PT_TW<u8>, u8>
#define texPAL8PT_TW texture_TW<convPAL8PT_TW<u8>, u8>
#define texPAL4_VQ texture_VQ<convPAL4_TW<u16>, u16>
#define texPAL8_VQ texture_VQ<convPAL8_TW<u16>, u16>
#define texPAL4_VQ32 texture_VQ<convPAL4_TW<u32>, u32>
#define texPAL8_VQ32 texture_VQ<convPAL8_TW<u32>, u32>

#define clamp(minv, maxv, x) ((x) < (minv) ? (minv) : (x) > (maxv) ? (maxv) : (x))

#define twop(x,y,bcx,bcy) (detwiddle[0][bcy][x]+detwiddle[1][bcx][y])

//pixel convertors !
#define pixelcvt_start_base(name,x,y,type) \
		struct name \
		{ \
			static const u32 xpp=x;\
			static const u32 ypp=y;	\
			__forceinline static void Convert(PixelBuffer<type>* pb,u8* data) \
		{

#define pixelcvt_start(name,x,y) pixelcvt_start_base(name, x, y, u16)
#define pixelcvt32_start(name,x,y) pixelcvt_start_base(name, x, y, u32)

#define pixelcvt_end } }
#define pixelcvt_next(name,x,y) pixelcvt_end;  pixelcvt_start(name,x,y)

u8* vq_codebook;
u32 palette_index;
bool KillTex=false;
u32 palette16_ram[1024];
u32 palette32_ram[1024];
u32 pal_hash_256[4];
u32 pal_hash_16[64];
bool palette_updated;
float fb_scale_x, fb_scale_y;

u32 detwiddle[2][11][1024];

static struct xbrz::ScalerCfg xbrz_cfg;

//struct PvrTexInfo;
template <class pixel_type> class PixelBuffer;
typedef void TexConvFP(PixelBuffer<u16>* pb,u8* p_in,u32 Width,u32 Height);
typedef void TexConvFP8(PixelBuffer<u8>* pb, u8* p_in, u32 Width, u32 Height);
typedef void TexConvFP32(PixelBuffer<u32>* pb,u8* p_in,u32 Width,u32 Height);

struct PvrTexInfo
{
	const char* name;
	int bpp;        //4/8 for pal. 16 for yuv, rgb, argb
	TextureType type;
/*
	// Conversion to 16 bpp
	TexConvFP *PL;
	TexConvFP *TW;
	TexConvFP *VQ;
	// Conversion to 32 bpp
	TexConvFP32 *PL32;
	TexConvFP32 *TW32;
	TexConvFP32 *VQ32;
	// Conversion to 8 bpp (palette)
	TexConvFP8 *TW8;
*/
 unsigned char PL;
 unsigned char TW;
 unsigned char VQ;
 unsigned char PL32;
 unsigned char TW32;
 unsigned char VQ32;
 unsigned char TW8;
};

static const u32 VQMipPoint[11] =
{
	0x00000,//1
	0x00001,//2
	0x00002,//4
	0x00006,//8
	0x00016,//16
	0x00056,//32
	0x00156,//64
	0x00556,//128
	0x01556,//256
	0x05556,//512
	0x15556//1024
};
static const u32 OtherMipPoint[11] =
{
	0x00003,//1
	0x00004,//2
	0x00008,//4
	0x00018,//8
	0x00058,//16
	0x00158,//32
	0x00558,//64
	0x01558,//128
	0x05558,//256
	0x15558,//512
	0x55558//1024
};

static const TextureType PAL_TYPE[4] = {
	TextureType::_5551, TextureType::_565, TextureType::_4444, TextureType::_8888
};

// Rough approximation of LoD bias from D adjust param, only used to increase LoD
const std::array<f32, 16> D_Adjust_LoD_Bias = {
		0.f, -4.f, -2.f, -1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f
};

static std::vector<vram_block*> VramLocks[VRAM_SIZE_MAX / PAGE_SIZE];
std::mutex vramlist_lock;

// Unpack to 16-bit word
static unsigned short ARGB1555( const unsigned short word )
{
 return( ((word>>15)&1) | (((word>>10) & 0x1F)<<11)  | (((word>>5) & 0x1F)<<6)  | (((word>>0) & 0x1F)<<1) );
}

static unsigned short ARGB565( const unsigned short word )
{
 return( (((word>>0)&0x1F)<<0) | (((word>>5)&0x3F)<<5) | (((word>>11)&0x1F)<<11) );
}
	
static unsigned short ARGB4444( const unsigned short word )
{
 return( (((word>>0)&0xF)<<4) | (((word>>4)&0xF)<<8) | (((word>>8)&0xF)<<12) | (((word>>12)&0xF)<<0) );
}

static unsigned short ARGB8888( const unsigned short word )
{
 return( (((word>>4)&0xF)<<4) | (((word>>12)&0xF)<<8) | (((word>>20)&0xF)<<12) | (((word>>28)&0xF)<<0) );
}

// Unpack to 32-bit word

static unsigned int ARGB1555_32( const unsigned int word )
{
 return( ((word & 0x8000) ? 0xFF000000 : 0) | (((word >> 10) & 0x1F) << 3) | (((word >> 12) & 0x7) << 0) | (((word >> 5) & 0x1F) << 11) | (((word >> 7) & 0x7) << 8) | (((word >> 0) & 0x1F) << 19) | (((word >> 2) & 0x7) << 16) );
}

static unsigned int ARGB565_32( const unsigned int word )
{
 return( (((word >> 11) & 0x1F) << 3) | (((word >> 13) & 0x7) << 0) | (((word >> 5) & 0x3F) << 10) | (((word >> 9) & 0x3) << 8) | (((word >> 0) & 0x1F) << 19) | (((word >> 2) & 0x7) << 16) | 0xFF000000 );
}

static unsigned int ARGB4444_32( const unsigned int word )
{
 return( (((word >> 12) & 0xF) << 28) | (((word >> 12) & 0xF) << 24) | (((word >> 8) & 0xF) << 4) | (((word >> 8) & 0xF) << 0) | (((word >> 4) & 0xF) << 12) | (((word >> 4) & 0xF) << 8) | (((word >> 0) & 0xF) << 20) | (((word >> 0) & 0xF) << 16) );
}

static unsigned int ARGB8888_32( const unsigned int word )
{
 return( ((word >> 0) & 0xFF000000) | (((word >> 16) & 0xFF) << 0) | (((word >> 8) & 0xFF) << 8) | ((word & 0xFF) << 16) );
}

inline static u32 YUV422(s32 Y,s32 Yu,s32 Yv)
{
	Yu-=128;
	Yv-=128;

	s32 R = Y + Yv*11/8;            // Y + (Yv-128) * (11/8) ?
	s32 G = Y - (Yu*11 + Yv*22)/32; // Y - (Yu-128) * (11/8) * 0.25 - (Yv-128) * (11/8) * 0.5 ?
	s32 B = Y + Yu*110/64;          // Y + (Yu-128) * (11/8) * 1.25 ?

	return clamp(0, 255, R) | (clamp(0, 255, G) << 8) | (clamp(0, 255, B) << 16) | 0xFF000000;
}

static u32 twiddle_slow(u32 x,u32 y,u32 x_sz,u32 y_sz)
{
	u32 rv=0;//low 2 bits are directly passed  -> needs some misc stuff to work.However
			 //Pvr internally maps the 64b banks "as if" they were twiddled :p

	u32 sh=0;
	x_sz>>=1;
	y_sz>>=1;
	while(x_sz!=0 || y_sz!=0)
	{
		if (y_sz)
		{
			u32 temp=y&1;
			rv|=temp<<sh;

			y_sz>>=1;
			y>>=1;
			sh++;
		}
		if (x_sz)
		{
			u32 temp=x&1;
			rv|=temp<<sh;

			x_sz>>=1;
			x>>=1;
			sh++;
		}
	}	
	return rv;
}

static void BuildTwiddleTables()
{
	for (u32 s = 0; s < 11; s++)
	{
		u32 x_sz = 1024;
		u32 y_sz = 1 << s;
		for (u32 i = 0; i < x_sz; i++)
		{
			detwiddle[0][s][i] = twiddle_slow(i, 0, x_sz, y_sz);
			detwiddle[1][s][i] = twiddle_slow(0, i, y_sz, x_sz);
		}
	}
}

static OnLoad btt(&BuildTwiddleTables);
//
//Non twiddled
//
// 16-bit pixel buffer
pixelcvt_start(conv565_PL,4,1)
{
	//convert 4x1
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,ARGB565(p_in[0]));
	//1,0
	pb->prel(1,ARGB565(p_in[1]));
	//2,0
	pb->prel(2,ARGB565(p_in[2]));
	//3,0
	pb->prel(3,ARGB565(p_in[3]));
}
pixelcvt_next(conv1555_PL,4,1)
{
	//convert 4x1
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,ARGB1555(p_in[0]));
	//1,0
	pb->prel(1,ARGB1555(p_in[1]));
	//2,0
	pb->prel(2,ARGB1555(p_in[2]));
	//3,0
	pb->prel(3,ARGB1555(p_in[3]));
}
pixelcvt_next(conv4444_PL,4,1)
{
	//convert 4x1
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,ARGB4444(p_in[0]));
	//1,0
	pb->prel(1,ARGB4444(p_in[1]));
	//2,0
	pb->prel(2,ARGB4444(p_in[2]));
	//3,0
	pb->prel(3,ARGB4444(p_in[3]));
}
pixelcvt_end;

// 32-bit pixel buffer
pixelcvt32_start(conv565_PL32,4,1)
{
	//convert 4x1
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,ARGB565_32(p_in[0]));
	//1,0
	pb->prel(1,ARGB565_32(p_in[1]));
	//2,0
	pb->prel(2,ARGB565_32(p_in[2]));
	//3,0
	pb->prel(3,ARGB565_32(p_in[3]));
}
pixelcvt_end;
pixelcvt32_start(conv1555_PL32,4,1)
{
	//convert 4x1
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,ARGB1555_32(p_in[0]));
	//1,0
	pb->prel(1,ARGB1555_32(p_in[1]));
	//2,0
	pb->prel(2,ARGB1555_32(p_in[2]));
	//3,0
	pb->prel(3,ARGB1555_32(p_in[3]));
}
pixelcvt_end;
pixelcvt32_start(conv4444_PL32,4,1)
{
	//convert 4x1
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,ARGB4444_32(p_in[0]));
	//1,0
	pb->prel(1,ARGB4444_32(p_in[1]));
	//2,0
	pb->prel(2,ARGB4444_32(p_in[2]));
	//3,0
	pb->prel(3,ARGB4444_32(p_in[3]));
}
pixelcvt_end;
pixelcvt32_start(convYUV_PL,4,1)
{
	//convert 4x1 4444 to 4x1 8888
	u32* p_in=(u32*)data;


	s32 Y0 = (p_in[0]>>8) &255; //
	s32 Yu = (p_in[0]>>0) &255; //p_in[0]
	s32 Y1 = (p_in[0]>>24) &255; //p_in[3]
	s32 Yv = (p_in[0]>>16) &255; //p_in[2]

	//0,0
	pb->prel(0,YUV422(Y0,Yu,Yv));
	//1,0
	pb->prel(1,YUV422(Y1,Yu,Yv));

	//next 4 bytes
	p_in+=1;

	Y0 = (p_in[0]>>8) &255; //
	Yu = (p_in[0]>>0) &255; //p_in[0]
	Y1 = (p_in[0]>>24) &255; //p_in[3]
	Yv = (p_in[0]>>16) &255; //p_in[2]

	//0,0
	pb->prel(2,YUV422(Y0,Yu,Yv));
	//1,0
	pb->prel(3,YUV422(Y1,Yu,Yv));
}
pixelcvt_end;

//
//twiddled
//
// 16-bit pixel buffer
pixelcvt_start(conv565_TW,2,2)
{
	//convert 4x1 565 to 4x1 8888
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,0,ARGB565(p_in[0]));
	//0,1
	pb->prel(0,1,ARGB565(p_in[1]));
	//1,0
	pb->prel(1,0,ARGB565(p_in[2]));
	//1,1
	pb->prel(1,1,ARGB565(p_in[3]));
}
pixelcvt_next(conv1555_TW,2,2)
{
	//convert 4x1 565 to 4x1 8888
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,0,ARGB1555(p_in[0]));
	//0,1
	pb->prel(0,1,ARGB1555(p_in[1]));
	//1,0
	pb->prel(1,0,ARGB1555(p_in[2]));
	//1,1
	pb->prel(1,1,ARGB1555(p_in[3]));
}
pixelcvt_next(conv4444_TW,2,2)
{
	//convert 4x1 565 to 4x1 8888
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,0,ARGB4444(p_in[0]));
	//0,1
	pb->prel(0,1,ARGB4444(p_in[1]));
	//1,0
	pb->prel(1,0,ARGB4444(p_in[2]));
	//1,1
	pb->prel(1,1,ARGB4444(p_in[3]));
}
pixelcvt_end;

// 32-bit pixel buffer
pixelcvt32_start(conv565_TW32,2,2)
{
	//convert 4x1 565 to 4x1 8888
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,0,ARGB565_32(p_in[0]));
	//0,1
	pb->prel(0,1,ARGB565_32(p_in[1]));
	//1,0
	pb->prel(1,0,ARGB565_32(p_in[2]));
	//1,1
	pb->prel(1,1,ARGB565_32(p_in[3]));
}
pixelcvt_end;
pixelcvt32_start(conv1555_TW32,2,2)
{
	//convert 4x1 565 to 4x1 8888
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,0,ARGB1555_32(p_in[0]));
	//0,1
	pb->prel(0,1,ARGB1555_32(p_in[1]));
	//1,0
	pb->prel(1,0,ARGB1555_32(p_in[2]));
	//1,1
	pb->prel(1,1,ARGB1555_32(p_in[3]));
}
pixelcvt_end;
pixelcvt32_start(conv4444_TW32,2,2)
{
	//convert 4x1 565 to 4x1 8888
	u16* p_in=(u16*)data;
	//0,0
	pb->prel(0,0,ARGB4444_32(p_in[0]));
	//0,1
	pb->prel(0,1,ARGB4444_32(p_in[1]));
	//1,0
	pb->prel(1,0,ARGB4444_32(p_in[2]));
	//1,1
	pb->prel(1,1,ARGB4444_32(p_in[3]));
}
pixelcvt_end;

pixelcvt32_start(convYUV_TW,2,2)
{
	//convert 4x1 4444 to 4x1 8888
	u16* p_in=(u16*)data;


	s32 Y0 = (p_in[0]>>8) &255; //
	s32 Yu = (p_in[0]>>0) &255; //p_in[0]
	s32 Y1 = (p_in[2]>>8) &255; //p_in[3]
	s32 Yv = (p_in[2]>>0) &255; //p_in[2]

	//0,0
	pb->prel(0,0,YUV422(Y0,Yu,Yv));
	//1,0
	pb->prel(1,0,YUV422(Y1,Yu,Yv));

	//next 4 bytes
	//p_in+=2;

	Y0 = (p_in[1]>>8) &255; //
	Yu = (p_in[1]>>0) &255; //p_in[0]
	Y1 = (p_in[3]>>8) &255; //p_in[3]
	Yv = (p_in[3]>>0) &255; //p_in[2]

	//0,1
	pb->prel(0,1,YUV422(Y0,Yu,Yv));
	//1,1
	pb->prel(1,1,YUV422(Y1,Yu,Yv));
}
pixelcvt_end;

// 16-bit && 32-bit pixel buffers
template<class pixel_size>
struct convPAL4_TW
{
 static const u32 xpp=4;
 static const u32 ypp=4;

__forceinline static void Convert(PixelBuffer<pixel_size>* pb,u8* data)
{
 u8* p_in=(u8*)data;
 u32* pal= sizeof(pixel_size) == 2 ? &palette16_ram[palette_index] : &palette32_ram[palette_index];

 pb->prel(0,0,pal[p_in[0]&0xF]);
 pb->prel(0,1,pal[(p_in[0]>>4)&0xF]);p_in++;
 pb->prel(1,0,pal[p_in[0]&0xF]);
 pb->prel(1,1,pal[(p_in[0]>>4)&0xF]);p_in++;

 pb->prel(0,2,pal[p_in[0]&0xF]);
 pb->prel(0,3,pal[(p_in[0]>>4)&0xF]);p_in++;
 pb->prel(1,2,pal[p_in[0]&0xF]);
 pb->prel(1,3,pal[(p_in[0]>>4)&0xF]);p_in++;

 pb->prel(2,0,pal[p_in[0]&0xF]);
 pb->prel(2,1,pal[(p_in[0]>>4)&0xF]);p_in++;
 pb->prel(3,0,pal[p_in[0]&0xF]);
 pb->prel(3,1,pal[(p_in[0]>>4)&0xF]);p_in++;

 pb->prel(2,2,pal[p_in[0]&0xF]);
 pb->prel(2,3,pal[(p_in[0]>>4)&0xF]);p_in++;
 pb->prel(3,2,pal[p_in[0]&0xF]);
 pb->prel(3,3,pal[(p_in[0]>>4)&0xF]);p_in++;
}

};

// Palette 4bpp -> 8bpp
template<class pixel_size>
struct convPAL4PT_TW
{
 static const u32 xpp=4;
 static const u32 ypp=4;

__forceinline static void Convert(PixelBuffer<pixel_size>* pb,u8* data)
{
	u8* p_in = (u8 *)data;

	pb->prel(0, 0, p_in[0] & 0xF);
	pb->prel(0, 1, (p_in[0] >> 4) & 0xF); p_in++;
	pb->prel(1, 0, p_in[0] & 0xF);
	pb->prel(1, 1, (p_in[0] >> 4) & 0xF); p_in++;

	pb->prel(0, 2, p_in[0] & 0xF);
	pb->prel(0, 3, (p_in[0] >> 4) & 0xF); p_in++;
	pb->prel(1, 2, p_in[0] & 0xF);
	pb->prel(1, 3, (p_in[0] >> 4) & 0xF); p_in++;

	pb->prel(2, 0, p_in[0] & 0xF);
	pb->prel(2, 1, (p_in[0] >> 4) & 0xF); p_in++;
	pb->prel(3, 0, p_in[0] & 0xF);
	pb->prel(3, 1, (p_in[0] >> 4) & 0xF); p_in++;

	pb->prel(2, 2, p_in[0] & 0xF);
	pb->prel(2, 3, (p_in[0] >> 4) & 0xF); p_in++;
	pb->prel(3, 2, p_in[0] & 0xF);
	pb->prel(3, 3, (p_in[0] >> 4) & 0xF); p_in++;
}

};

template<class pixel_size>
struct convPAL8_TW
{
 static const u32 xpp=2;
 static const u32 ypp=4;

__forceinline static void Convert(PixelBuffer<pixel_size>* pb,u8* data)
{
	u8* p_in=(u8*)data;
	u32* pal= sizeof(pixel_size) == 2 ? &palette16_ram[palette_index] : &palette32_ram[palette_index];

	pb->prel(0,0,pal[p_in[0]]);p_in++;
	pb->prel(0,1,pal[p_in[0]]);p_in++;
	pb->prel(1,0,pal[p_in[0]]);p_in++;
	pb->prel(1,1,pal[p_in[0]]);p_in++;

	pb->prel(0,2,pal[p_in[0]]);p_in++;
	pb->prel(0,3,pal[p_in[0]]);p_in++;
	pb->prel(1,2,pal[p_in[0]]);p_in++;
	pb->prel(1,3,pal[p_in[0]]);p_in++;
}

};
// Palette 8bpp -> 8bpp (untwiddle only)
template<class pixel_size>
struct convPAL8PT_TW
{
 static const u32 xpp=2;
 static const u32 ypp=4;

__forceinline static void Convert(PixelBuffer<pixel_size>* pb,u8* data)
{
	u8* p_in = (u8 *)data;

	pb->prel(0, 0, p_in[0]); p_in++;
	pb->prel(0, 1, p_in[0]); p_in++;
	pb->prel(1, 0, p_in[0]); p_in++;
	pb->prel(1, 1, p_in[0]); p_in++;

	pb->prel(0, 2, p_in[0]); p_in++;
	pb->prel(0, 3, p_in[0]); p_in++;
	pb->prel(1, 2, p_in[0]); p_in++;
	pb->prel(1, 3, p_in[0]); p_in++;
}

};
//handler functions
template<class PixelConvertor, class pixel_type>
void texture_PL(PixelBuffer<pixel_type>* pb,u8* p_in,u32 Width,u32 Height)
{
	pb->amove(0,0);

	Height/=PixelConvertor::ypp;
	Width/=PixelConvertor::xpp;

	for (u32 y=0;y<Height;y++)
	{
		for (u32 x=0;x<Width;x++)
		{
			u8* p = p_in;
			PixelConvertor::Convert(pb,p);
			p_in+=8;

			pb->rmovex(PixelConvertor::xpp);
		}
		pb->rmovey(PixelConvertor::ypp);
	}
}

template<class PixelConvertor, class pixel_type>
void texture_TW(PixelBuffer<pixel_type>* pb,u8* p_in,u32 Width,u32 Height)
{
	pb->amove(0, 0);

	const u32 divider = PixelConvertor::xpp * PixelConvertor::ypp;

	const u32 bcx = bitscanrev(Width);
	const u32 bcy = bitscanrev(Height);

	for (u32 y = 0; y < Height; y += PixelConvertor::ypp)
	{
		for (u32 x = 0; x < Width; x += PixelConvertor::xpp)
		{
			u8* p = &p_in[(twop(x, y, bcx, bcy) / divider) << 3];
			PixelConvertor::Convert(pb, p);

			pb->rmovex(PixelConvertor::xpp);
		}
		pb->rmovey(PixelConvertor::ypp);
	}
}

template<class PixelConvertor, class pixel_type>
void texture_VQ(PixelBuffer<pixel_type>* pb,u8* p_in,u32 Width,u32 Height)
{
	p_in += 256 * 4 * 2;	// Skip VQ codebook
	pb->amove(0, 0);

	const u32 divider = PixelConvertor::xpp * PixelConvertor::ypp;
	const u32 bcx = bitscanrev(Width);
	const u32 bcy = bitscanrev(Height);

	for (u32 y = 0; y < Height; y += PixelConvertor::ypp)
	{
		for (u32 x = 0; x < Width; x += PixelConvertor::xpp)
		{
			u8 p = p_in[twop(x, y, bcx, bcy) / divider];
			PixelConvertor::Convert(pb, &vq_codebook[p * 8]);

			pb->rmovex(PixelConvertor::xpp);
		}
		pb->rmovey(PixelConvertor::ypp);
	}
}

/*
End of the header export.
*/

static const PvrTexInfo format[8] =
{	// name     bpp Final format			   Planar		Twiddled	 VQ				Planar(32b)    Twiddled(32b)  VQ (32b)      Palette (8b)
 {"1555",    16, TextureType::_5551,   0, 1, 2,  0, 1, 2, 2 },
 { "565",    16, TextureType::_565,    3, 4, 5,  3, 4, 5, 2 },
 {"4444",    16, TextureType::_4444,   6, 7, 8,  6, 7, 8, 2 },
 { "yuv",    16, TextureType::_8888,  16,16,16,  9,10,11, 2 },
 {"bumpmap", 16, TextureType::_4444,   9,10,11,  6, 7, 8, 2 },
 {"pal4",     4, TextureType::_5551,  16,12,13, 16,12,13, 0 },
 {"pal8",     8, TextureType::_5551,  16,14,15, 16,14,15, 1 },
// Not supported (1555)
 {"ns/1555", 0, TextureType::_5551,   16,16,16, 16,16,16, 2 }
};

static const TexConvFP8 *texfa8[3] = { texPAL4PT_TW, texPAL8PT_TW, nullptr };

static const TexConvFP *texfa16[17] = { tex1555_PL, tex1555_TW, tex1555_VQ, tex565_PL, tex565_TW, tex565_VQ, tex4444_PL, tex4444_TW, tex4444_VQ, texBMP_PL, texBMP_TW, texBMP_VQ, texPAL4_TW, texPAL4_VQ, texPAL8_TW, texPAL8_VQ, nullptr };

static const TexConvFP32 *texfa32[17] = { tex1555_PL32, tex1555_TW32, tex1555_VQ32, tex565_PL32, tex565_TW32, tex565_VQ32, tex4444_PL32, tex4444_TW32, tex4444_VQ32, texYUV422_PL, texYUV422_TW, texYUV422_VQ, texPAL4_TW32, texPAL4_VQ32, texPAL8_TW32, texPAL8_VQ32, nullptr };

static void rend_text_invl(vram_block* bl);

//input : address in the yyyyyxxxxx format
//output : address in the xyxyxyxy format
//U : x resolution , V : y resolution
//twiddle works on 64b words

void palette_update()
{
	if (!pal_needs_update)
		return;
	pal_needs_update = false;
	palette_updated = true;

	switch(PAL_RAM_CTRL&3)
	{
	case 0:
		for (int i=0;i<1024;i++)
		{
			palette16_ram[i] = ARGB1555(PALETTE_RAM[i]);
			palette32_ram[i] = ARGB1555_32(PALETTE_RAM[i]);
		}
		break;

	case 1:
		for (int i=0;i<1024;i++)
		{
			palette16_ram[i] = ARGB565(PALETTE_RAM[i]);
			palette32_ram[i] = ARGB565_32(PALETTE_RAM[i]);
		}
		break;

	case 2:
		for (int i=0;i<1024;i++)
		{
			palette16_ram[i] = ARGB4444(PALETTE_RAM[i]);
			palette32_ram[i] = ARGB4444_32(PALETTE_RAM[i]);
		}
		break;

	case 3:
		for (int i=0;i<1024;i++)
		{
			palette16_ram[i] = ARGB8888(PALETTE_RAM[i]);
			palette32_ram[i] = ARGB8888_32(PALETTE_RAM[i]);
		}
		break;
	}
	for (int i = 0; i < 64; i++)
		pal_hash_16[i] = XXH32(&PALETTE_RAM[i << 4], 16 * 4, 7);
	for (int i = 0; i < 4; i++)
		pal_hash_256[i] = XXH32(&PALETTE_RAM[i << 8], 256 * 4, 7);
}

//List functions
//
void vramlock_list_remove(vram_block* block)
{
	u32 base = block->start / PAGE_SIZE;
	u32 end = block->end / PAGE_SIZE;

	for (u32 i = base; i <= end; i++)
	{
		std::vector<vram_block*>& list = VramLocks[i];
		for (auto& lock : list)
		{
			if (lock == block)
				lock = nullptr;
		}
	}
}
 
void vramlock_list_add(vram_block* block)
{
	u32 base = block->start / PAGE_SIZE;
	u32 end = block->end / PAGE_SIZE;

	for (u32 i = base; i <= end; i++)
	{
		std::vector<vram_block*>& list = VramLocks[i];
		// If the list is empty then we need to protect vram, otherwise it's already been done
		if (list.empty() || std::all_of(list.begin(), list.end(), [](vram_block *block) { return block == nullptr; }))
			_vmem_protect_vram(i * PAGE_SIZE, PAGE_SIZE);
		auto it = std::find(list.begin(), list.end(), nullptr);
		if (it != list.end())
			*it = block;
		else
			list.push_back(block);
	}
}

void libCore_vramlock_Lock(u32 start_offset64, u32 end_offset64, BaseTextureCacheData *texture)
{
	vram_block* block=(vram_block* )malloc(sizeof(vram_block));
 
	if (end_offset64>(VRAM_SIZE-1))
	{
		WARN_LOG(PVR, "vramlock_Lock_64: end_offset64>(VRAM_SIZE-1) \n Tried to lock area out of vram , possibly bug on the pvr plugin");
		end_offset64=(VRAM_SIZE-1);
	}

	if (start_offset64>end_offset64)
	{
		WARN_LOG(PVR, "vramlock_Lock_64: start_offset64>end_offset64 \n Tried to lock negative block , possibly bug on the pvr plugin");
		start_offset64=0;
	}

	

	block->end=end_offset64;
	block->start=start_offset64;
	block->len=end_offset64-start_offset64+1;
	block->userdata = texture;
	block->type=64;

	{
		std::lock_guard<std::mutex> lock(vramlist_lock);

		if (texture->lock_block == nullptr)
		{
			// This also protects vram if needed
			vramlock_list_add(block);
			texture->lock_block = block;
		}
		else
			free(block);
	}
}

bool VramLockedWriteOffset(size_t offset)
{
	if (offset >= VRAM_SIZE)
		return false;

	size_t addr_hash = offset / PAGE_SIZE;
	std::vector<vram_block *>& list = VramLocks[addr_hash];

	{
		std::lock_guard<std::mutex> lockguard(vramlist_lock);

		for (auto& lock : list)
		{
			if (lock != nullptr)
			{
				rend_text_invl(lock);

				if (lock != nullptr)
				{
					ERROR_LOG(PVR, "Error : pvr is supposed to remove lock");
					die("Invalid state");
				}
			}
		}
		list.clear();

		_vmem_unprotect_vram((u32)(offset & ~PAGE_MASK), PAGE_SIZE);
	}

	return true;
}

bool VramLockedWrite(u8* address)
{
	u32 offset = _vmem_get_vram_offset(address);
	if (offset == (u32)-1)
		return false;
	return VramLockedWriteOffset(offset);
}

//unlocks mem
//also frees the handle
static void libCore_vramlock_Unlock_block_wb(vram_block* block)
{
	vramlock_list_remove(block);
	free(block);
}

void libCore_vramlock_Unlock_block(vram_block* block)
{
	std::lock_guard<std::mutex> lock(vramlist_lock);
	libCore_vramlock_Unlock_block_wb(block);
}

#ifndef TARGET_NO_OPENMP
static inline int getThreadCount()
{
	int tcount = omp_get_num_procs() - 1;
	if (tcount < 1)
		tcount = 1;
	return std::min(tcount, (int)config::MaxThreads);
}

template<typename Func>
void parallelize(Func func, int start, int end)
{
	int tcount = getThreadCount();
#pragma omp parallel num_threads(tcount)
	{
		int num_threads = omp_get_num_threads();
		int thread = omp_get_thread_num();
		int chunk = (end - start) / num_threads;
		func(start + chunk * thread,
				num_threads == thread + 1 ? end
						: (start + chunk * (thread + 1)));
	}
}
#endif

void UpscalexBRZ(int factor, u32* source, u32* dest, int width, int height, bool has_alpha)
{
#ifndef TARGET_NO_OPENMP
	parallelize([=](int start, int end) {
		xbrz::scale(factor, source, dest, width, height, has_alpha ? xbrz::ColorFormat::ARGB : xbrz::ColorFormat::RGB,
				xbrz_cfg, start, end);
	}, 0, height);
#else
	xbrz::scale(factor, source, dest, width, height, has_alpha ? xbrz::ColorFormat::ARGB : xbrz::ColorFormat::RGB, xbrz_cfg);
#endif
}

void BaseTextureCacheData::PrintTextureName()
{
	char str[512];
	sprintf(str, "Texture: %s", GetPixelFormatName());

	if (tcw.VQ_Comp)
		strcat(str, " VQ");
	else if (tcw.ScanOrder == 0)
		strcat(str, " TW");
	else if (tcw.StrideSel)
		strcat(str, " Stride");

	if (tcw.ScanOrder == 0 && tcw.MipMapped)
		strcat(str, " MM");
	if (tsp.FilterMode != 0)
		strcat(str, " Bilinear");

	sprintf(str + strlen(str), " %dx%d @ 0x%X", 8 << tsp.TexU, 8 << tsp.TexV, tcw.TexAddr << 3);
	std::string id = GetId();
	sprintf(str + strlen(str), " id=%s", id.c_str());
	DEBUG_LOG(RENDERER, "%s", str);
}

//true if : dirty or paletted texture and hashes don't match
bool BaseTextureCacheData::NeedsUpdate() {
	bool rc = dirty != 0;
	if (tex_type != TextureType::_8)
	{
		if (tcw.PixelFmt == PixelPal4 && palette_hash != pal_hash_16[tcw.PalSelect])
			rc = true;
		else if (tcw.PixelFmt == PixelPal8 && palette_hash != pal_hash_256[tcw.PalSelect >> 4])
			rc = true;
	}

	return rc;
}

bool BaseTextureCacheData::Delete()
{
	if (custom_load_in_progress > 0)
		return false;

	{
		std::lock_guard<std::mutex> lock(vramlist_lock);
		if (lock_block)
			libCore_vramlock_Unlock_block_wb(lock_block);
		lock_block = nullptr;
	}

	free(custom_image_data);

	return true;
}

void BaseTextureCacheData::Create()
{
 const unsigned char theid = (tcw.PixelFmt == PixelReserved) ? Pixel1555 : tcw.PixelFmt;
//Reset state info ..
 Updates = 0;
 dirty = FrameCount;
 lock_block = nullptr;
 custom_image_data = nullptr;
 custom_load_in_progress = 0;
//decode info from tsp/tcw into the texture struct
//texture format table entry
// tex = &format[tcw.PixelFmt == PixelReserved ? Pixel1555 : tcw.PixelFmt];
 bitdepth = format[theid].bpp;
//texture start address
 sa_tex = (tcw.TexAddr << 3) & VRAM_MASK;
//data texture start address (modified for MIPs, as needed)
 sa = sa_tex;
 texwidth = 8 << tsp.TexU;
 texheight = 8 << tsp.TexV;
//PAL texture
//	if (tex->bpp == 4)
 if ( bitdepth == 4 ) palette_index = tcw.PalSelect << 4;
//	else if (tex->bpp == 8)
 else if ( bitdepth == 8 ) palette_index = (tcw.PalSelect >> 4) << 8;
//	texconv8 = nullptr;
 texconv8 = 2;
/* Notice the obvious... */
 if ( ( format[theid].PL != 16 ) || ( format[theid].PL32 != 16 ) ) isplanar = 1;
 else isplanar = 0;

 org_type = format[theid].type;
//	if (tcw.ScanOrder && (tex->PL || tex->PL32))
	if ( tcw.ScanOrder && isplanar )
	{
		//Texture is stored 'planar' in memory, no deswizzle is needed
		//verify(tcw.VQ_Comp==0);
		if (tcw.VQ_Comp != 0)
		{
			WARN_LOG(RENDERER, "Warning: planar texture with VQ set (invalid)");
			tcw.VQ_Comp = 0;
		}
		if (tcw.MipMapped != 0)
		{
			WARN_LOG(RENDERER, "Warning: planar texture with mipmaps (invalid)");
			tcw.MipMapped = 0;
		}

		//Planar textures support stride selection, mostly used for non power of 2 textures (videos)
		int stride = texwidth;

		if (tcw.StrideSel)
			stride = (TEXT_CONTROL & 31) * 32;

		//Call the format specific conversion code
/*
		texconv = tex->PL;
		texconv32 = tex->PL32;
*/
 texconv = format[theid].PL;
 texconv32 = format[theid].PL32;
		//calculate the size, in bytes, for the locking
		size = stride * texheight * bitdepth / 8;
	}
	else
	{
		tcw.ScanOrder = 0;
		tcw.StrideSel = 0;
		// Quake 3 Arena uses one
		if (tcw.MipMapped)
			// Mipmapped texture must be square and TexV is ignored
			texheight = texwidth;

		if (tcw.VQ_Comp)
		{
//			verify(tex->VQ != NULL || tex->VQ32 != NULL);
			verify( format[theid].VQ != 16 || format[theid].VQ32 != 16 );
			vq_codebook = sa;

			if (tcw.MipMapped)
				sa += VQMipPoint[tsp.TexU + 3];
/*
			texconv = tex->VQ;
			texconv32 = tex->VQ32;
			size = w * h / 8;
*/
 texconv = format[theid].VQ;
 texconv32 = format[theid].VQ32;
		size = texwidth * texheight / 8;
		}
		else
		{
//			verify(tex->TW != NULL || tex->TW32 != NULL);
  verify( format[theid].TW != 16 || format[theid].TW32 != 16 );

			if (tcw.MipMapped)
				sa += OtherMipPoint[tsp.TexU + 3] * bitdepth / 8;
/*
			texconv = tex->TW;
			texconv32 = tex->TW32;
			texconv8 = tex->TW8;
			size = w * h * tex->bpp / 8;
*/
 texconv = format[theid].TW;
 texconv32 = format[theid].TW32;
 texconv8 = format[theid].TW8;
		size = texwidth * texheight * bitdepth / 8;
		}

	}
}

void BaseTextureCacheData::ComputeHash()
{
	texture_hash = XXH32(&vram[sa], size, 7);
	if (IsPaletted())
		texture_hash ^= palette_hash;
	old_texture_hash = texture_hash;
	texture_hash ^= tcw.full & 0xFC000000;	// everything but texaddr, reserved and stride
}

void BaseTextureCacheData::Update()
{
	//texture state tracking stuff
	Updates++;
	dirty=0;

//	tex_type = tex->type;
	tex_type = org_type;

	bool has_alpha = false;
	if (IsPaletted())
	{
		if (IsGpuHandledPaletted(tsp, tcw))
			tex_type = TextureType::_8;
		else
		{
			tex_type = PAL_TYPE[PAL_RAM_CTRL&3];
			if (tex_type != TextureType::_565)
				has_alpha = true;
		}

		// Get the palette hash to check for future updates
		if (tcw.PixelFmt == PixelPal4)
			palette_hash = pal_hash_16[tcw.PalSelect];
		else
			palette_hash = pal_hash_256[tcw.PalSelect >> 4];
	}

	::palette_index = this->palette_index; // might be used if pal. tex
	::vq_codebook = &vram[vq_codebook];    // might be used if VQ tex

	//texture conversion work
	u32 stride = texwidth;

	if (tcw.StrideSel && tcw.ScanOrder && isplanar )
		stride = (TEXT_CONTROL & 31) * 32;

	u32 original_h = texheight;

	if (sa_tex > VRAM_SIZE || size == 0 || sa + size > VRAM_SIZE)
	{
		if (sa < VRAM_SIZE && sa + size > VRAM_SIZE && tcw.ScanOrder && stride > 0)
		{
			// Shenmue Space Harrier mini-arcade loads a texture that goes beyond the end of VRAM
			// but only uses the top portion of it
			texheight = (VRAM_SIZE - sa) * 8 / stride / bitdepth;
			size = stride * texheight * bitdepth / 8;
		}
		else
		{
			WARN_LOG(RENDERER, "Warning: invalid texture. Address %08X %08X size %d", sa_tex, sa, size);
			return;
		}
	}
	if (config::CustomTextures)
		custom_texture.LoadCustomTextureAsync(this);

	void *temp_tex_buffer = NULL;
	u32 upscaled_w = texwidth;
	u32 upscaled_h = texheight;

	PixelBuffer<u16> pb16;
	PixelBuffer<u32> pb32;
	PixelBuffer<u8> pb8;

	// Figure out if we really need to use a 32-bit pixel buffer
	bool textureUpscaling = config::TextureUpscale > 1
			// Don't process textures that are too big
			&& (int)(texwidth * texheight) <= config::MaxFilteredTextureSize * config::MaxFilteredTextureSize
			// Don't process YUV textures
			&& tcw.PixelFmt != PixelYUV;
	bool need_32bit_buffer = true;
	if (!textureUpscaling
		&& (!IsPaletted() || tex_type != TextureType::_8888)
//		&& texconv != NULL
		&& texconv != 16
		&& !Force32BitTexture(tex_type))
		need_32bit_buffer = false;
	// TODO avoid upscaling/depost. textures that change too often

	bool mipmapped = IsMipmapped() && !config::DumpTextures;

//	if (texconv32 != NULL && need_32bit_buffer)
	if (texconv32 != 16 && need_32bit_buffer)
	{
		if (textureUpscaling)
			// don't use mipmaps if upscaling
			mipmapped = false;
		// Force the texture type since that's the only 32-bit one we know
		tex_type = TextureType::_8888;

		if (mipmapped)
		{
			pb32.init(texwidth, texheight, true);
			for (u32 i = 0; i <= tsp.TexU + 3u; i++)
			{
				pb32.set_mipmap(i);
				u32 vram_addr;
				if (tcw.VQ_Comp)
				{
					vram_addr = sa_tex + VQMipPoint[i];
					if (i == 0)
					{
						PixelBuffer<u32> pb0;
						pb0.init(2, 2 ,false);
//						texconv32(&pb0, (u8*)&vram[vram_addr], 2, 2);
texfa32[texconv32](&pb0, (u8*)&vram[vram_addr], 2, 2);
						*pb32.data() = *pb0.data(1, 1);
						continue;
					}
				}
				else
					vram_addr = sa_tex + OtherMipPoint[i] * bitdepth / 8;
				if (tcw.PixelFmt == PixelYUV && i == 0)
					// Special case for YUV at 1x1 LoD
//					format[Pixel565].TW32(&pb32, &vram[vram_addr], 1, 1);
 texfa32[format[Pixel565].TW32](&pb32, &vram[vram_addr], 1, 1);
				else
//					texconv32(&pb32, &vram[vram_addr], 1 << i, 1 << i);
texfa32[texconv32](&pb32, &vram[vram_addr], 1 << i, 1 << i);

			}
			pb32.set_mipmap(0);
		}
		else
		{
			pb32.init(texwidth, texheight);
//			texconv32(&pb32, (u8*)&vram[sa], stride, texheight);
texfa32[texconv32](&pb32, (u8*)&vram[sa], stride, texheight);

			// xBRZ scaling
			if (textureUpscaling)
			{
				PixelBuffer<u32> tmp_buf;
				tmp_buf.init(texwidth * config::TextureUpscale, texheight * config::TextureUpscale);

				if (tcw.PixelFmt == Pixel1555 || tcw.PixelFmt == Pixel4444)
					// Alpha channel formats. Palettes with alpha are already handled
					has_alpha = true;
				UpscalexBRZ(config::TextureUpscale, pb32.data(), tmp_buf.data(), texwidth, texheight, has_alpha);
				pb32.steal_data(tmp_buf);
				upscaled_w *= config::TextureUpscale;
				upscaled_h *= config::TextureUpscale;
			}
		}
		temp_tex_buffer = pb32.data();
	}
//	else if (texconv8 != NULL && tex_type == TextureType::_8)
	else if (texconv8 != 2 && tex_type == TextureType::_8)
	{
		if (mipmapped)
		{
			pb8.init(texwidth, texheight, true);
			for (u32 i = 0; i <= tsp.TexU + 3u; i++)
			{
				pb8.set_mipmap(i);
				u32 vram_addr = sa_tex + OtherMipPoint[i] * bitdepth / 8;
//				texconv8(&pb8, &vram[vram_addr], 1 << i, 1 << i);
texfa8[texconv8](&pb8, &vram[vram_addr], 1 << i, 1 << i);
			}
			pb8.set_mipmap(0);
		}
		else
		{
			pb8.init(texwidth, texheight);
//			texconv8(&pb8, &vram[sa], stride, texheight);
texfa8[texconv8](&pb8, &vram[sa], stride, texheight);
		}
		temp_tex_buffer = pb8.data();
	}
//	else if (texconv != NULL)
	else if (texconv != 16)
	{
		if (mipmapped)
		{
			pb16.init(texwidth, texheight, true);
			for (u32 i = 0; i <= tsp.TexU + 3u; i++)
			{
				pb16.set_mipmap(i);
				u32 vram_addr;
				if (tcw.VQ_Comp)
				{
					vram_addr = sa_tex + VQMipPoint[i];
					if (i == 0)
					{
						PixelBuffer<u16> pb0;
						pb0.init(2, 2 ,false);
//						texconv(&pb0, (u8*)&vram[vram_addr], 2, 2);
texfa16[texconv](&pb0, (u8*)&vram[vram_addr], 2, 2);
						*pb16.data() = *pb0.data(1, 1);
						continue;
					}
				}
				else
					vram_addr = sa_tex + OtherMipPoint[i] * bitdepth / 8;
//				texconv(&pb16, (u8*)&vram[vram_addr], 1 << i, 1 << i);
texfa16[texconv](&pb16, (u8*)&vram[vram_addr], 1 << i, 1 << i);
			}
			pb16.set_mipmap(0);
		}
		else
		{
			pb16.init(texwidth, texheight);
//			texconv(&pb16,(u8*)&vram[sa],stride,texheight);
texfa16[texconv](&pb16,(u8*)&vram[sa],stride,texheight);
		}
		temp_tex_buffer = pb16.data();
	}
	else
	{
		//fill it in with a temp color
		WARN_LOG(RENDERER, "UNHANDLED TEXTURE");
		pb16.init(texwidth, texheight);
		memset(pb16.data(), 0x80, texwidth * texheight * 2);
		temp_tex_buffer = pb16.data();
		mipmapped = false;
	}
	// Restore the original texture height if it was constrained to VRAM limits above
	texheight = original_h;

	//lock the texture to detect changes in it
	libCore_vramlock_Lock(sa_tex, sa + size - 1, this);

	UploadToGPU(upscaled_w, upscaled_h, (u8*)temp_tex_buffer, IsMipmapped(), mipmapped);
	if (config::DumpTextures)
	{
		ComputeHash();
		custom_texture.DumpTexture(texture_hash, upscaled_w, upscaled_h, tex_type, temp_tex_buffer);
		NOTICE_LOG(RENDERER, "Dumped texture %x.png. Old hash %x", texture_hash, old_texture_hash);
	}
	PrintTextureName();
}

void BaseTextureCacheData::CheckCustomTexture()
{
	if (IsCustomTextureAvailable())
	{
		tex_type = TextureType::_8888;
		UploadToGPU(custom_width, custom_height, custom_image_data, IsMipmapped(), false);
		free(custom_image_data);
		custom_image_data = NULL;
	}
}

/**/
bool BaseTextureCacheData::IsPaletted()
{
 return tcw.PixelFmt == PixelPal4 || tcw.PixelFmt == PixelPal8;
}

bool BaseTextureCacheData::IsMipmapped()
{
 return tcw.MipMapped != 0 && tcw.ScanOrder == 0 && config::UseMipmaps;
}

const char* BaseTextureCacheData::GetPixelFormatName()
{

 switch (tcw.PixelFmt)
{
  case Pixel1555: return "1555";
  case Pixel565: return "565";
  case Pixel4444: return "4444";
  case PixelYUV: return "yuv";
  case PixelBumpMap: return "bumpmap";
  case PixelPal4: return "pal4";
  case PixelPal8: return "pal8";
  default: return "unknown";
}

}

bool BaseTextureCacheData::IsCustomTextureAvailable()
{
 return custom_load_in_progress == 0 && custom_image_data != NULL;
}

bool BaseTextureCacheData::Force32BitTexture(TextureType type) const { return false; }

//BaseTextureCacheData::
bool IsGpuHandledPaletted( const TSP tsp, const TCW tcw )
{
// Some palette textures are handled on the GPU
// This is currently limited to textures using nearest filtering and not mipmapped.
// Enabling texture upscaling or dumping also disables this mode.
 return (tcw.PixelFmt == PixelPal4 || tcw.PixelFmt == PixelPal8) && config::TextureUpscale == 1	&& !config::DumpTextures && tsp.FilterMode == 0 && !tcw.MipMapped && !tcw.VQ_Comp;
}

/**/

void ReadFramebuffer(PixelBuffer<u32>& pb, int& width, int& height)
{
	width = (FB_R_SIZE.fb_x_size + 1) << 1;     // in 16-bit words
	height = FB_R_SIZE.fb_y_size + 1;
	int modulus = (FB_R_SIZE.fb_modulus - 1) << 1;

	int bpp;
	switch (FB_R_CTRL.fb_depth)
	{
		case fbde_0555:
		case fbde_565:
			bpp = 2;
			break;
		case fbde_888:
			bpp = 3;
			width = (width * 2) / 3;		// in pixels
			modulus = (modulus * 2) / 3;	// in pixels
			break;
		case fbde_C888:
			bpp = 4;
			width /= 2;             // in pixels
			modulus /= 2;           // in pixels
			break;
		default:
			die("Invalid framebuffer format\n");
			bpp = 4;
			break;
	}

	u32 addr = FB_R_SOF1;
	if (SPG_CONTROL.interlace)
	{
		if (width == modulus && FB_R_SOF2 == FB_R_SOF1 + width * bpp)
		{
			// Typical case alternating even and odd lines -> take the whole buffer at once
			modulus = 0;
			height *= 2;
		}
		else
		{
			addr = SPG_STATUS.fieldnum ? FB_R_SOF2 : FB_R_SOF1;
		}
	}

	pb.init(width, height);
	u8 *dst = (u8*)pb.data();

	switch (FB_R_CTRL.fb_depth)
	{
		case fbde_0555:    // 555 RGB
			for (int y = 0; y < height; y++)
			{
				for (int i = 0; i < width; i++)
				{
					u16 src = pvr_read32p<u16>(addr);
					*dst++ = (((src >> 10) & 0x1F) << 3) + FB_R_CTRL.fb_concat;
					*dst++ = (((src >> 5) & 0x1F) << 3) + FB_R_CTRL.fb_concat;
					*dst++ = (((src >> 0) & 0x1F) << 3) + FB_R_CTRL.fb_concat;
					*dst++ = 0xFF;
					addr += bpp;
				}
				addr += modulus * bpp;
			}
			break;

		case fbde_565:    // 565 RGB
			for (int y = 0; y < height; y++)
			{
				for (int i = 0; i < width; i++)
				{
					u16 src = pvr_read32p<u16>(addr);
					*dst++ = (((src >> 11) & 0x1F) << 3) + FB_R_CTRL.fb_concat;
					*dst++ = (((src >> 5) & 0x3F) << 2) + (FB_R_CTRL.fb_concat & 3);
					*dst++ = (((src >> 0) & 0x1F) << 3) + FB_R_CTRL.fb_concat;
					*dst++ = 0xFF;
					addr += bpp;
				}
				addr += modulus * bpp;
			}
			break;
		case fbde_888:		// 888 RGB
			for (int y = 0; y < height; y++)
			{
				for (int i = 0; i < width; i += 4)
				{
					u32 src = pvr_read32p<u32>(addr);
					*dst++ = src >> 16;
					*dst++ = src >> 8;
					*dst++ = src;
					*dst++ = 0xFF;
					addr += 4;
					if (i + 1 >= width)
						break;
					u32 src2 = pvr_read32p<u32>(addr);
					*dst++ = src2 >> 8;
					*dst++ = src2;
					*dst++ = src >> 24;
					*dst++ = 0xFF;
					addr += 4;
					if (i + 2 >= width)
						break;
					u32 src3 = pvr_read32p<u32>(addr);
					*dst++ = src3;
					*dst++ = src2 >> 24;
					*dst++ = src2 >> 16;
					*dst++ = 0xFF;
					addr += 4;
					if (i + 3 >= width)
						break;
					*dst++ = src3 >> 24;
					*dst++ = src3 >> 16;
					*dst++ = src3 >> 8;
					*dst++ = 0xFF;
				}
				addr += modulus * bpp;
			}
			break;
		case fbde_C888:     // 0888 RGB
			for (int y = 0; y < height; y++)
			{
				for (int i = 0; i < width; i++)
				{
					u32 src = pvr_read32p<u32>(addr);
					*dst++ = src >> 16;
					*dst++ = src >> 8;
					*dst++ = src;
					*dst++ = 0xFF;
					addr += bpp;
				}
				addr += modulus * bpp;
			}
			break;
	}
}

void WriteTextureToVRam(u32 width, u32 height, u8 *data, u16 *dst, u32 fb_w_ctrl_in, u32 linestride)
{
	FB_W_CTRL_type fb_w_ctrl;
	if (fb_w_ctrl_in != ~0u)
		fb_w_ctrl.full = fb_w_ctrl_in;
	else
		fb_w_ctrl = FB_W_CTRL;
	u32 padding = (linestride == ~0u ? FB_W_LINESTRIDE.stride * 8 : linestride);
	if (padding != 0)
		padding = padding / 2 - width;

	const u16 kval_bit = (fb_w_ctrl.fb_kval & 0x80) << 8;
	const u8 fb_alpha_threshold = fb_w_ctrl.fb_alpha_threshold;

	u8 *p = data;

	for (u32 l = 0; l < height; l++) {
		switch(fb_w_ctrl.fb_packmode)
		{
		case 0: //0x0   0555 KRGB 16 bit  (default)	Bit 15 is the value of fb_kval[7].
			for (u32 c = 0; c < width; c++) {
				*dst++ = (((p[0] >> 3) & 0x1F) << 10) | (((p[1] >> 3) & 0x1F) << 5) | ((p[2] >> 3) & 0x1F) | kval_bit;
				p += 4;
			}
			break;
		case 1: //0x1   565 RGB 16 bit
			for (u32 c = 0; c < width; c++) {
				*dst++ = (((p[0] >> 3) & 0x1F) << 11) | (((p[1] >> 2) & 0x3F) << 5) | ((p[2] >> 3) & 0x1F);
				p += 4;
			}
			break;
		case 2: //0x2   4444 ARGB 16 bit
			for (u32 c = 0; c < width; c++) {
				*dst++ = (((p[0] >> 4) & 0xF) << 8) | (((p[1] >> 4) & 0xF) << 4) | ((p[2] >> 4) & 0xF) | (((p[3] >> 4) & 0xF) << 12);
				p += 4;
			}
			break;
		case 3://0x3    1555 ARGB 16 bit    The alpha value is determined by comparison with the value of fb_alpha_threshold.
			for (u32 c = 0; c < width; c++) {
				*dst++ = (((p[0] >> 3) & 0x1F) << 10) | (((p[1] >> 3) & 0x1F) << 5) | ((p[2] >> 3) & 0x1F) | (p[3] > fb_alpha_threshold ? 0x8000 : 0);
				p += 4;
			}
			break;
		}
		dst += padding;
	}
}

static void rend_text_invl(vram_block* bl)
{
	BaseTextureCacheData* tcd = (BaseTextureCacheData*)bl->userdata;
	tcd->dirty = FrameCount;
	tcd->lock_block = nullptr;

	libCore_vramlock_Unlock_block_wb(bl);
}

#ifdef TEST_AUTOMATION
#include <stb_image_write.h>

void dump_screenshot(u8 *buffer, u32 width, u32 height, bool alpha, u32 rowPitch, bool invertY)
{
	stbi_flip_vertically_on_write((int)invertY);
	stbi_write_png("screenshot.png", width, height, alpha ? 4 : 3, buffer, rowPitch);
}
#endif

/*
Exported from the header...
*/
void MakeFogTexture(u8 *tex_data)
{
 int i = 0, j = 128, k = 0;
 u8 *fog_table = (u8 *)FOG_TABLE;

 for ( ; i < 128; i++, j++, k += 3 )
{
  tex_data[i] = fog_table[k];
  k++;
  tex_data[j] = fog_table[k];
/*
  tex_data[i] = fog_table[i * 4];
  tex_data[i + 128] = fog_table[i * 4 + 1];
*/
}

}

#include <array>
#include "spg.h"
#include "hw/holly_intc.h"
#include "hw/sb.h"
#include "hw/sh4/sh4_sched.h"
#include "input/gamepad_device.h"
#include "oslib/oslib.h"
#include "rend/TexCache.h"

//SPG emulation; Scanline/Raster beam registers & interrupts

static u32 in_vblank;
#ifndef TEST_DC1
static u32 clc_pvr_scanline;
#endif
static u32 pvr_numscanlines = 512;
static u32 prv_cur_scanline = -1;
static u32 vblk_cnt;

//static float last_fps;

//54 mhz pixel clock
#define PIXEL_CLOCK (54*1000*1000/2)
static u32 Line_Cycles;
static u32 Frame_Cycles;

#ifndef TEST_DC1
int render_end_schid;
int vblank_schid;
#else
u32 clc_pvr_scanline;
#endif

static std::array<double, 4> real_times;
static std::array<u64, 4> cpu_cycles;
static u32 cpu_time_idx;
bool SH4FastEnough;
u32 fskip;

static u32 lightgun_line = 0xffff;
static u32 lightgun_hpos;
static bool maple_int_pending;

static void setFramebufferScaling()
{
	float scale_x = 1.f;
	float scale_y = 1.f;

	if (SPG_CONTROL.interlace)
	{
		//u32 interl_mode=VO_CONTROL.field_mode;
		//if (interl_mode==2)//3 will be funny =P
		//  scale_y=0.5f;//single interlace
		//else
			scale_y = 1.f;
	}
	else
	{
		if (FB_R_CTRL.vclk_div)
			scale_y = 1.0f;//non interlaced VGA mode has full resolution :)
		else
			scale_y = 0.5f;//non interlaced modes have half resolution
	}

//	rend_set_fb_scale(scale_x, scale_y);
 fb_scale_x = scale_x;
 fb_scale_y = scale_y;
}

void CalculateSync()
{
	u32 pixel_clock = PIXEL_CLOCK / (FB_R_CTRL.vclk_div ? 1 : 2);

	// We need to calculate the pixel clock

	pvr_numscanlines = SPG_LOAD.vcount + 1;

	Line_Cycles = (u32)((u64)SH4_MAIN_CLOCK * (u64)(SPG_LOAD.hcount + 1) / (u64)pixel_clock);
	if (SPG_CONTROL.interlace)
		Line_Cycles /= 2;

	setFramebufferScaling();
	
	Frame_Cycles = pvr_numscanlines * Line_Cycles;
	prv_cur_scanline = 0;
#ifndef TEST_DC1
	sh4_sched_request(vblank_schid, Line_Cycles);
#else
	sh4_sched_request( 0, Line_Cycles);
#endif
}

//called from sh4 context , should update pvr/ta state and everything else
#ifdef TEST_DC1
int spg_line_sched( void )
{
#else
static int spg_line_sched( int tag, int cycl, int jit )
{
	clc_pvr_scanline += cycl;
#endif
	while (clc_pvr_scanline >=  Line_Cycles)//60 ~hertz = 200 mhz / 60=3333333.333 cycles per screen refresh
	{
		//ok .. here , after much effort , we did one line
		//now , we must check for raster beam interrupts and vblank
		prv_cur_scanline=(prv_cur_scanline+1)%pvr_numscanlines;
		clc_pvr_scanline -= Line_Cycles;
		//Check for scanline interrupts -- really need to test the scanline values
		
		if (SPG_VBLANK_INT.vblank_in_interrupt_line_number == prv_cur_scanline)
		{
			if (maple_int_pending)
			{
				maple_int_pending = false;
				SB_MDST = 0;
				asic_RaiseInterrupt(holly_MAPLE_DMA);
			}
			asic_RaiseInterrupt(holly_SCANINT1);
		}

		if (SPG_VBLANK_INT.vblank_out_interrupt_line_number == prv_cur_scanline)
			asic_RaiseInterrupt(holly_SCANINT2);

		if (SPG_VBLANK.vstart == prv_cur_scanline)
			in_vblank=1;

		if (SPG_VBLANK.vbend == prv_cur_scanline)
			in_vblank=0;

		SPG_STATUS.vsync=in_vblank;
		SPG_STATUS.scanline=prv_cur_scanline;
		
		switch (SPG_HBLANK_INT.hblank_int_mode)
		{
		case 0x0:
			if (prv_cur_scanline == SPG_HBLANK_INT.line_comp_val)
				asic_RaiseInterrupt(holly_HBLank);
			break;
		case 0x2:
			asic_RaiseInterrupt(holly_HBLank);
			break;
		default:
			die("Unimplemented HBLANK INT mode");
			break;
		}

		//Vblank start
		if (prv_cur_scanline==0)
		{
			if (SPG_CONTROL.interlace)
				SPG_STATUS.fieldnum=~SPG_STATUS.fieldnum;
			else
				SPG_STATUS.fieldnum=0;

			rend_vblank();

			double now = os_GetSeconds() * 1000000.0;
			cpu_time_idx = (cpu_time_idx + 1) % cpu_cycles.size();
			if (cpu_cycles[cpu_time_idx] != 0)
			{
				u32 cycle_span = (u32)(sh4_sched_now64() - cpu_cycles[cpu_time_idx]);
				double time_span = now - real_times[cpu_time_idx];
				double cpu_speed = ((double)cycle_span / time_span) / (SH4_MAIN_CLOCK / 100000000);
				SH4FastEnough = cpu_speed >= 85.0;
			}
			else
				SH4FastEnough = false;
			cpu_cycles[cpu_time_idx] = sh4_sched_now64();
			real_times[cpu_time_idx] = now;

#ifdef TEST_AUTOMATION
			replay_input();
#endif

#if !defined(NDEBUG) || defined(DEBUGFAST)
			vblk_cnt++;
			if ((os_GetSeconds()-last_fps)>2)
			{
				static int Last_FC;
				double ts=os_GetSeconds()-last_fps;
				double spd_fps=(FrameCount-Last_FC)/ts;
				double spd_vbs=vblk_cnt/ts;
				double spd_cpu=spd_vbs*Frame_Cycles;
				spd_cpu/=1000000;	//mrhz kthx
				double fullvbs=(spd_vbs/spd_cpu)*200;
				double mv=VertexCount/ts/(spd_cpu/200);
				char mv_c=' ';

				Last_FC=FrameCount;

				if (mv>750)
				{
					mv/=1000;	//KV
					mv_c='K';
				}
				if (mv>750)
				{
					mv/=1000;	//
					mv_c='M';
				}
				VertexCount=0;
				vblk_cnt=0;

				const char* mode=0;
				const char* res=0;

				res=SPG_CONTROL.interlace?"480i":"240p";

				if (SPG_CONTROL.NTSC==0 && SPG_CONTROL.PAL==1)
					mode="PAL";
				else if (SPG_CONTROL.NTSC==1 && SPG_CONTROL.PAL==0)
					mode="NTSC";
				else
				{
					res=SPG_CONTROL.interlace?"480i":"480p";
					mode="VGA";
				}

				double frames_done=spd_cpu/2;
				double mspdf=1/frames_done*1000;

				double full_rps = spd_fps + fskip / ts;

				INFO_LOG(COMMON, "%s/%c - %4.2f - %4.2f - V: %4.2f (%.2f, %s%s%4.2f) R: %4.2f+%4.2f VTX: %4.2f%c",
					VER_SHORTNAME,'n',mspdf,spd_cpu*100/200,spd_vbs,
					spd_vbs/full_rps,mode,res,fullvbs,
					spd_fps,fskip/ts
					, mv, mv_c);
				
				fskip=0;
				last_fps=os_GetSeconds();
			}
#endif
		}
		if (lightgun_line != 0xffff && lightgun_line == prv_cur_scanline)
		{
			maple_int_pending = false;
			SPG_TRIGGER_POS = ((lightgun_line & 0x3FF) << 16) | (lightgun_hpos & 0x3FF);
			SB_MDST = 0;
			asic_RaiseInterrupt(holly_MAPLE_DMA);
			lightgun_line = 0xffff;
		}
	}

	//interrupts
	//0
	//vblank_in_interrupt_line_number
	//vblank_out_interrupt_line_number
	//vstart
	//vbend
	//pvr_numscanlines
	u32 min_scanline=prv_cur_scanline+1;
	u32 min_active=pvr_numscanlines;

	if (min_scanline<SPG_VBLANK_INT.vblank_in_interrupt_line_number)
		min_active = std::min(min_active,SPG_VBLANK_INT.vblank_in_interrupt_line_number);

	if (min_scanline<SPG_VBLANK_INT.vblank_out_interrupt_line_number)
		min_active = std::min(min_active,SPG_VBLANK_INT.vblank_out_interrupt_line_number);

	if (min_scanline<SPG_VBLANK.vstart)
		min_active = std::min(min_active,SPG_VBLANK.vstart);

	if (min_scanline<SPG_VBLANK.vbend)
		min_active = std::min(min_active,SPG_VBLANK.vbend);

	if (lightgun_line != 0xffff && min_scanline < lightgun_line)
		min_active = std::min(min_active, lightgun_line);

	min_active = std::max(min_active,min_scanline);

	return (min_active - prv_cur_scanline) * Line_Cycles;
}

void read_lightgun_position(int x, int y)
{
	static u8 flip;
	maple_int_pending = true;
	if (y < 0 || y >= 480 || x < 0 || x >= 640)
	{
		// Off screen
		lightgun_line = 0xffff;
	}
	else
	{
		lightgun_line = y / (SPG_CONTROL.interlace ? 2 : 1) + SPG_VBLANK_INT.vblank_out_interrupt_line_number;
		// For some reason returning the same position twice makes it register off screen
		lightgun_hpos = (x + 286) ^ flip;
		flip ^= 1;
	}
}

#ifdef TEST_DC1
int rend_end_sch(void)
#else
static int rend_end_sch( int tag, int cycl, int jitt )
#endif
{
	asic_RaiseInterrupt(holly_RENDER_DONE);
	asic_RaiseInterrupt(holly_RENDER_DONE_isp);
	asic_RaiseInterrupt(holly_RENDER_DONE_vd);
	rend_end_render();
	return 0;
}

bool spg_Init()
{
#ifndef TEST_DC1
	render_end_schid=sh4_sched_register(0,&rend_end_sch);
	vblank_schid=sh4_sched_register(0,&spg_line_sched);
#endif
	return true;
}

void spg_Term()
{
}

void spg_Reset(/*bool hard*/)
{
	CalculateSync();

	SH4FastEnough = false;
	cpu_time_idx = 0;
	cpu_cycles.fill(0);
	real_times.fill(0.0);
}

void SetREP(TA_context* cntx)
{
 int cyclo = 0;

/*
	if (cntx)
		sh4_sched_request(render_end_schid, 500000 * 3);
	else
		sh4_sched_request(render_end_schid, 4096);
*/
 if (cntx) cyclo = 1500000;
 else cyclo = 4096;
#ifndef TEST_DC1
 sh4_sched_request( render_end_schid, cyclo );
#else
 sh4_sched_request( 1, cyclo );
#endif
}

void spg_Serialize(void **data, unsigned int *total_size)
{
	REICAST_S(in_vblank);
	REICAST_S(clc_pvr_scanline);
	REICAST_S(maple_int_pending);
	REICAST_S(pvr_numscanlines);
	REICAST_S(prv_cur_scanline);
	REICAST_S(Line_Cycles);
	REICAST_S(Frame_Cycles);
	REICAST_S(lightgun_line);
	REICAST_S(lightgun_hpos);
}

void spg_Unserialize(void **data, unsigned int *total_size, serialize_version_enum version)
{
	REICAST_US(in_vblank);
	REICAST_US(clc_pvr_scanline);
	if (version != VCUR_LIBRETRO && version < V5)
	{
		u32 i;
		REICAST_US(pvr_numscanlines);
		REICAST_US(prv_cur_scanline);
		REICAST_US(vblk_cnt);
		REICAST_US(Line_Cycles);
		REICAST_US(Frame_Cycles);
		REICAST_SKIP(8);		// speed_load_mspdf
		REICAST_US(i);			// mips_counter
		REICAST_SKIP(8);		// full_rps
		REICAST_US(i);			// fskip
	}
	else if (version >= V12)
	{
		REICAST_US(maple_int_pending);
		if (version >= V14)
		{
			REICAST_US(pvr_numscanlines);
			REICAST_US(prv_cur_scanline);
			REICAST_US(Line_Cycles);
			REICAST_US(Frame_Cycles);
			REICAST_US(lightgun_line);
			REICAST_US(lightgun_hpos);
		}
	}
	if (version < V14)
		CalculateSync();
	else
		setFramebufferScaling();
}


#include "types.h"
#include "sh4_interrupts.h"

#ifdef TEST_DC1
#include "../aica.h"
#include "../aica_if.h"
#include "../gdromv3.h"
#include "../maple_if.h"
#include "../modem.h"
#include "../pvr/spg.h"
#include "modules.h"
#endif
/* Many stupid macros here... */
#include "sh4_core.h"
#include "sh4_sched.h"
#include "oslib/oslib.h"

//sh4 scheduler

/*

	register handler
	request callback at time

	single fire events only

	sh4_sched_register(id)
	sh4_sched_request(id, in_cycles)

	sh4_sched_now()

*/
u64 sh4_sched_ffb;

#ifndef TEST_DC1
std::vector<sched_list> sch_list;	// using list as external inside a macro confuses clang and msc

#else
sched_list sch_list[11] = { {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {5, -1, -1}, {6, -1, -1}, {7, -1, -1}, {8, -1, -1}, {9, -1, -1}, {10, -1, -1} };

int (*letscalbfa[8])( void ) = { spg_line_sched, rend_end_sch, GDRomschd, DreamcastSecond, AicaUpdate, maple_schd, dma_end_sched, 0 };
const size_t list_size = 11;
#endif
static int sh4_sched_next_id=-1;

u32 sh4_sched_remaining(size_t id, u32 reference)
{
	if (sch_list[id].end != -1)
		return sch_list[id].end - reference;
	else
		return -1;
}

u32 sh4_sched_remaining(size_t id)
{
	return sh4_sched_remaining(id, sh4_sched_now());
}

void sh4_sched_ffts()
{
#ifndef TEST_DC1
 const size_t list_size = sch_list.size();
#endif
 u32 diff=-1;
 int slot=-1;
 size_t i = 0;

 for ( ; i < list_size; i++ )
{

  if (sh4_sched_remaining(i)<diff)
{
   slot=i;
   diff=sh4_sched_remaining(i);
}

}

 sh4_sched_ffb-=Sh4cntx.sh4_sched_next;
 sh4_sched_next_id=slot;

	if (slot!=-1)
		Sh4cntx.sh4_sched_next=diff;
	else
		Sh4cntx.sh4_sched_next=SH4_MAIN_CLOCK;

	sh4_sched_ffb+=Sh4cntx.sh4_sched_next;
}

#ifndef TEST_DC1
int sh4_sched_register(int tag, sh4_sched_callback* ssc)
{
	sched_list t={ssc,tag,-1,-1};

	sch_list.push_back(t);

	return sch_list.size()-1;
}
#else
void sh4_sched_reset(void)
{
 size_t i = 0;

 for ( ; i < list_size; i++ )
{
  sch_list[i].tag = i;
  sch_list[i].start = -1;
  sch_list[i].end = -1;
}

}
#endif

/*
	Return current cycle count, in 32 bits (wraps after 21 dreamcast seconds)
*/
u32 sh4_sched_now()
{
	return sh4_sched_ffb-Sh4cntx.sh4_sched_next;
}

/*
	Return current cycle count, in 64 bits (effectively never wraps)
*/
u64 sh4_sched_now64()
{
	return sh4_sched_ffb-Sh4cntx.sh4_sched_next;
}
void sh4_sched_request(size_t id, int cycles)
{
	verify(cycles== -1 || (cycles >= 0 && cycles <= SH4_MAIN_CLOCK));

	sch_list[id].start=sh4_sched_now();

	if (cycles == -1)
	{
		sch_list[id].end = -1;
	}
	else
	{
		sch_list[id].end = sch_list[id].start + cycles;
		if (sch_list[id].end == -1)
			sch_list[id].end++;
	}

	sh4_sched_ffts();
}

/* Returns how much time has passed for this callback */
static int sh4_sched_elapsed(size_t id)
{
	if (sch_list[id].end!=-1)
	{
		int rv=sh4_sched_now()-sch_list[id].start;
		sch_list[id].start=sh4_sched_now();
		return rv;
	}
	else
		return -1;
}

static void handle_cb(size_t id)
{
 const int remain = sch_list[id].end - sch_list[id].start;
 const int jitter = sh4_sched_elapsed(id) - remain;
 int re_sch = 0;
#ifndef TEST_DC1
 sch_list[id].end = -1;

 re_sch=sch_list[id].cb(sch_list[id].tag,remain,jitter);
#else
 sch_list[id].end = -1;
/* TMU, modem and BBA are 7 */
 if ( id > 7 )
{
  re_sch = sched_tmu_cb( id - 8, jitter );
}
else
{
  if ( id == 0 ) clc_pvr_scanline += remain;

  re_sch = letscalbfa[id]();
}
#endif

 if (re_sch > 0) sh4_sched_request(id, std::max(0, re_sch - jitter));
}

void sh4_sched_tick(int cycles)
{
/*
 Sh4cntx.sh4_sched_time+=cycles;
 Sh4cntx.sh4_sched_next-=cycles;
*/
#ifndef TEST_DC1
 const size_t list_size = sch_list.size();
#endif
 u32 fztime = 0, remaining = 0;
 size_t i = 0;

 if (Sh4cntx.sh4_sched_next<0)
{
  fztime=sh4_sched_now()-cycles;

  if (sh4_sched_next_id!=-1)
{

   for ( ; i < list_size; i++)
{
    remaining = sh4_sched_remaining(i, fztime);
#ifndef TEST_DC1
    verify(remaining >= 0 || remaining == -1);

    if (remaining >= 0 && remaining <= (u32)cycles) handle_cb(i);
#else
//    verify( remaining == (u32)-1 );
    verify(remaining >= 0 || remaining == -1);

    if ( remaining >= 0 && remaining <= (u32)cycles ) handle_cb(i);
#endif
}

}

  sh4_sched_ffts();
}

}

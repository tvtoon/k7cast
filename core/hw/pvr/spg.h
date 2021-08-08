#pragma once
#include "ta_ctx.h"

extern bool SH4FastEnough;

bool spg_Init();
void spg_Term();
void spg_Reset(/*bool Manual*/);
void spg_Serialize(void **data, unsigned int *total_size);
void spg_Unserialize(void **data, unsigned int *total_size, serialize_version_enum version);

void CalculateSync();
void read_lightgun_position(int x, int y);
void SetREP(TA_context* cntx);

#ifdef TEST_DC1
int spg_line_sched( void );
int rend_end_sch(void);

extern u32 clc_pvr_scanline;
#endif

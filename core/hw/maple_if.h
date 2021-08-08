#pragma once
#include "maple_devs.h"

extern maple_device* MapleDevices[MAPLE_PORTS][6];

void maple_Init();
void maple_Reset(bool Manual);
void maple_Term();
void maple_ReconnectDevices();

void maple_vblank();

#ifdef TEST_DC1
int maple_schd( void );
#endif

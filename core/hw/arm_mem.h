#pragma once
#include "types.h"
#include "hw/aica_if.h"

template <u32 sz,class T>
T arm_ReadReg(u32 addr);
template <u32 sz,class T>
void arm_WriteReg(u32 addr,T data);

template<int sz,typename T>
static inline T DYNACALL ReadMemArm(u32 addr)
{
	addr&=0x00FFFFFF;
	if (addr<0x800000)
	{
		T rv=*(T*)&aica_ram[addr&(ARAM_MASK-(sz-1))];
		
		if (unlikely(sz==4 && addr&3))
		{
			u32 sf=(addr&3)*8;
			return (rv>>sf) | (rv<<(32-sf));
		}
		else
			return rv;
	}
	else
	{
		return arm_ReadReg<sz,T>(addr);
	}
}

template<int sz,typename T>
static inline void DYNACALL WriteMemArm(u32 addr,T data)
{
	addr&=0x00FFFFFF;
	if (addr<0x800000)
	{
		*(T*)&aica_ram[addr&(ARAM_MASK-(sz-1))]=data;
	}
	else
	{
		arm_WriteReg<sz,T>(addr,data);
	}
}

#define arm_ReadMem8 ReadMemArm<1,u8>
#define arm_ReadMem16 ReadMemArm<2,u16>
#define arm_ReadMem32 ReadMemArm<4,u32>

#define arm_WriteMem8 WriteMemArm<1,u8>
#define arm_WriteMem16 WriteMemArm<2,u16>
#define arm_WriteMem32 WriteMemArm<4,u32>

extern bool aica_interr;
extern u32 aica_reg_L;
extern bool e68k_out;
extern u32 e68k_reg_L;
extern u32 e68k_reg_M;

void update_armintc();
void libARM_InterruptChange(u32 bits, u32 L);

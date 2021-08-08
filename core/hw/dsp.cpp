#include "dsp.h"

/*
	DSP rec_v1

	Tries to emulate a guesstimation of the aica dsp, by directly emitting x86 opcodes.

	This was my first dsp implementation, as implemented for nullDC 1.0.3. 
	
	This was derived from a schematic I drew for the dsp, based on 
	liberal interpretation of known specs, the saturn dsp, digital 
	electronics assumptions, as well as "best-fitted" my typical 
	test game suite.


	Initial code by skmp, now part of the reicast project.
	See LICENSE & COPYRIGHT files further details
*/

alignas(4096) dsp_t dsp;

//float format is ?
u16 DYNACALL PACK(s32 val)
{
	int sign = (val >> 23) & 0x1;
	u32 temp = (val ^ (val << 1)) & 0xFFFFFF;
	int exponent = 0;
	for (int k = 0; k < 12; k++)
	{
		if (temp & 0x800000)
			break;
		temp <<= 1;
		exponent += 1;
	}
	if (exponent < 12)
		val <<= exponent;
	else
		val <<= 11;
	val = (val >> 11) & 0x7FF;	// avoid sign extension of mantissa
	val |= sign << 15;
	val |= exponent << 11;

	return (u16)val;
}

s32 DYNACALL UNPACK(u16 val)
{
	int sign = (val >> 15) & 0x1;
	int exponent = (val >> 11) & 0xF;
	int mantissa = val & 0x7FF;
	s32 uval = mantissa << 11;
	uval |= sign << 22;		// take the sign in bit 22
	if (exponent > 11)
		exponent = 11;		// cap exponent to 11 for denormals
	else
		uval ^= 1 << 22;	// reverse bit 22 for normals
	uval |= sign << 23;		// actual sign bit
	uval <<= 8;
	uval >>= 8;
	uval >>= exponent;

	return uval;
}

void DecodeInst(const u32 *IPtr, _INST *i)
{
	i->TRA = (IPtr[0] >> 9) & 0x7F;
	i->TWT = IPtr[0] & 0x100;
	i->TWA = (IPtr[0] >> 1) & 0x7F;

	i->XSEL = IPtr[1] & 0x8000;
	i->YSEL = (IPtr[1] >> 13) & 3;
	i->IRA = (IPtr[1] >> 7) & 0x3F;
	i->IWT = IPtr[1] & 0x40;
	i->IWA = (IPtr[1] >> 1) & 0x1F;

	i->TABLE = IPtr[2] & 0x8000;
	i->MWT = IPtr[2] & 0x4000;
	i->MRD = IPtr[2] & 0x2000;
	i->EWT = IPtr[2] & 0x1000;
	i->EWA = (IPtr[2] >> 8) & 0x0F;
	i->ADRL = IPtr[2] & 0x80;
	i->FRCL = IPtr[2] & 0x40;
	i->SHIFT = (IPtr[2] >> 4) & 3;
	i->YRL = IPtr[2] & 8;
	i->NEGB = IPtr[2] & 4;
	i->ZERO = IPtr[2] & 2;
	i->BSEL = IPtr[2] & 1;

	i->NOFL = IPtr[3] & 0x8000;
	i->MASA = (IPtr[3] >> 9) & 0x3f;
	i->ADREB = IPtr[3] & 0x100;
	i->NXADR = IPtr[3] & 0x80;
}

#if FEAT_DSPREC != DYNAREC_NONE

void dsp_init()
{
	memset(&dsp, 0, sizeof(dsp));
	dsp.RBL = 0x8000 - 1;
	dsp.RBP = 0;
	dsp.regs.MDEC_CT = 1;
	dsp.dyndirty = true;

	dsp_rec_init();
}

void dsp_step()
{
	if (dsp.dyndirty)
	{
		dsp.dyndirty = false;
		dsp_recompile();
	}
	if (dsp.Stopped)
		return;
	dsp_rec_step();
}

void dsp_writenmem(u32 addr)
{
	if (addr >= 0x3400 && addr < 0x3C00)
	{
		dsp.dyndirty = true;
	}
	else if (addr >= 0x4000 && addr < 0x4400)
	{
		// TODO proper sharing of memory with sh4 through DSPData
		memset(dsp.TEMP, 0, sizeof(dsp.TEMP));
	}
	else if (addr >= 0x4400 && addr < 0x4500)
	{
		// TODO proper sharing of memory with sh4 through DSPData
		memset(dsp.MEMS, 0, sizeof(dsp.MEMS));
	}
}

void dsp_term()
{
}

#endif

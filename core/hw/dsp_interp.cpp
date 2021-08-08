//
// Audio Overload SDK
//
// Copyright (c) 2007-2009 R. Belmont and Richard Bannister, and others.
// All rights reserved.
//

#include "build.h"

#if FEAT_DSPREC != DYNAREC_JIT

#include "dsp.h"
#include "aica.h"
#include "aica_if.h"

#ifdef NDEBUG
#undef verify
#define verify(...)
#endif

void AICADSP_Init(struct dsp_t *DSP)
{
	memset(DSP, 0, sizeof(*DSP));
	DSP->RBL = 0x8000 - 1;
	DSP->Stopped = 1;
	dsp.regs.MDEC_CT = 1;
}

void AICADSP_Step(struct dsp_t *DSP)
{
	s32 ACC = 0;		//26 bit
	s32 SHIFTED = 0;	//24 bit
	s32 X = 0;			//24 bit
	s32 Y = 0;			//13 bit
	s32 B = 0;			//26 bit
	s32 INPUTS = 0;		//24 bit
	s32 MEMVAL[4] = {0};
	s32 FRC_REG = 0;	//13 bit
	s32 Y_REG = 0;		//24 bit
	u32 ADRS_REG = 0;	//13 bit

	if (DSP->Stopped)
		return;

#if 0
	int dump = 0;
	FILE *f = NULL;
	if (dump)
		f = fopen("dsp.txt", "wt");
#endif

	for (int step = 0; step < 128; ++step)
	{
		u32 *IPtr = DSPData->MPRO + step * 4;

		if (IPtr[0] == 0 && IPtr[1] == 0 && IPtr[2] == 0 && IPtr[3] == 0)
		{
			// Empty instruction shortcut
			X = DSP->TEMP[DSP->regs.MDEC_CT & 0x7F];
			Y = FRC_REG;

			ACC = (((s64)X * (s64)Y) >> 12) + X;

			continue;
		}

		u32 TRA = (IPtr[0] >> 9) & 0x7F;
		bool TWT = IPtr[0] & 0x100;

		bool XSEL = IPtr[1] & 0x8000;
		u32 YSEL = (IPtr[1] >> 13) & 3;
		u32 IRA = (IPtr[1] >> 7) & 0x3F;
		bool IWT = IPtr[1] & 0x40;

		bool EWT = IPtr[2] & 0x1000;
		bool ADRL = IPtr[2] & 0x80;
		bool FRCL = IPtr[2] & 0x40;
		u32 SHIFT = (IPtr[2] >> 4) & 3;
		bool YRL = IPtr[2] & 8;
		bool NEGB = IPtr[2] & 4;
		bool ZERO = IPtr[2] & 2;
		bool BSEL = IPtr[2] & 1;

		u32 COEF = step;

		// operations are done at 24 bit precision
#if 0
#define DUMP(v)	printf(" " #v ": %04X",v);

		printf("%d: ",step);
		DUMP(ACC);
		DUMP(SHIFTED);
		DUMP(X);
		DUMP(Y);
		DUMP(B);
		DUMP(INPUTS);
		DUMP(MEMVAL);
		DUMP(FRC_REG);
		DUMP(Y_REG);
		DUMP(ADDR);
		DUMP(ADRS_REG);
		printf("\n");
#endif

		// INPUTS RW
		if (IRA <= 0x1f)
			INPUTS = DSP->MEMS[IRA];
		else if (IRA <= 0x2F)
			INPUTS = DSP->MIXS[IRA - 0x20] << 4;		// MIXS is 20 bit
		else if (IRA <= 0x31)
			INPUTS = DSPData->EXTS[IRA - 0x30] << 8;	// EXTS is 16 bits
		else
			INPUTS = 0;

		if (IWT)
		{
			u32 IWA = (IPtr[1] >> 1) & 0x1F;
			DSP->MEMS[IWA] = MEMVAL[step & 3];	// MEMVAL was selected in previous MRD
		}

		// Operand sel
		// B
		if (!ZERO)
		{
			if (BSEL)
				B = ACC;
			else
				B = DSP->TEMP[(TRA + DSP->regs.MDEC_CT) & 0x7F];
			if (NEGB)
				B = -B;
		}
		else
		{
			B = 0;
		}

		// X
		if (XSEL)
			X = INPUTS;
		else
			X = DSP->TEMP[(TRA + DSP->regs.MDEC_CT) & 0x7F];

		// Y
		if (YSEL == 0)
			Y = FRC_REG;
		else if (YSEL == 1)
			Y = ((s32)(s16)DSPData->COEF[COEF]) >> 3;	//COEF is 16 bits
		else if (YSEL == 2)
			Y = Y_REG >> 11;
		else if (YSEL == 3)
			Y = (Y_REG >> 4) & 0x0FFF;

		if (YRL)
			Y_REG = INPUTS;

		// Shifter
		// There's a 1-step delay at the output of the X*Y + B adder. So we use the ACC value from the previous step.
		if (SHIFT == 0 || SHIFT == 3)
			SHIFTED = ACC;
		else
			SHIFTED = ACC << 1;		// x2 scale

		if (SHIFT < 2)
			SHIFTED = std::min(std::max(SHIFTED, -0x00800000), 0x007FFFFF);

		// ACCUM
		ACC = (((s64)X * (s64)Y) >> 12) + B;

		if (TWT)
		{
			u32 TWA = (IPtr[0] >> 1) & 0x7F;
			DSP->TEMP[(TWA + DSP->regs.MDEC_CT) & 0x7F] = SHIFTED;
		}

		if (FRCL)
		{
			if (SHIFT == 3)
				FRC_REG = SHIFTED & 0x0FFF;
			else
				FRC_REG = SHIFTED >> 11;
		}

		if (step & 1)
		{
			bool MWT = IPtr[2] & 0x4000;
			bool MRD = IPtr[2] & 0x2000;

			if (MRD || MWT)
			{
				bool TABLE = IPtr[2] & 0x8000;

				//bool NOFL = IPtr[3] & 0x8000;
				//verify(!NOFL);
				u32 MASA = (IPtr[3] >> 9) & 0x3f;
				bool ADREB = IPtr[3] & 0x100;
				bool NXADR = IPtr[3] & 0x80;

				u32 ADDR = DSPData->MADRS[MASA];
				if (ADREB)
					ADDR += ADRS_REG & 0x0FFF;
				if (NXADR)
					ADDR++;
				if (!TABLE)
				{
					ADDR += DSP->regs.MDEC_CT;
					ADDR &= DSP->RBL;		// RBL is ring buffer length - 1
				}
				else
					ADDR &= 0xFFFF;

				ADDR <<= 1;					// Word -> byte address
				ADDR += DSP->RBP;			// RBP is already a byte address
				if (MRD)			// memory only allowed on odd. DoA inserts NOPs on even
				{
					//if (NOFL)
					//	MEMVAL[(step + 2) & 3] = (*(s16 *)&aica_ram[ADDR]) << 8;
					//else
						MEMVAL[(step + 2) & 3] = UNPACK(*(u16 *)&aica_ram[ADDR & ARAM_MASK]);
				}
				if (MWT)
				{
					// FIXME We should wait for the next step to copy stuff to SRAM (same as read)
					//if (NOFL)
					//	*(s16 *)&aica_ram[ADDR] = SHIFTED >> 8;
					//else
						*(u16 *)&aica_ram[ADDR & ARAM_MASK] = PACK(SHIFTED);
				}
			}
		}

		if (ADRL)
		{
			if (SHIFT == 3)
				ADRS_REG = SHIFTED >> 12;
			else
				ADRS_REG = INPUTS >> 16;
		}

		if (EWT)
		{
			u32 EWA = (IPtr[2] >> 8) & 0x0F;
			DSPData->EFREG[EWA] = SHIFTED >> 8;
		}

	}
	--DSP->regs.MDEC_CT;
	if (dsp.regs.MDEC_CT == 0)
		dsp.regs.MDEC_CT = dsp.RBL + 1;			// RBL is ring buffer length - 1

//	memset(DSP->MIXS, 0, sizeof(DSP->MIXS));
//  if(f)
//      fclose(f);
}

void AICADSP_Start(struct dsp_t *DSP)
{
	dsp.Stopped = 1;
	for (int i = 127; i >= 0; --i)
	{
		u32 *IPtr = DSPData->MPRO + i * 4;

		if (IPtr[0] != 0 || IPtr[1] != 0 || IPtr[2 ]!= 0 || IPtr[3] != 0)
		{
			DSP->Stopped = 0;
			//printf("DSP: starting %d steps\n", i + 1);

			break;
		}
	}
}

void dsp_init()
{
	AICADSP_Init(&dsp);
	AICADSP_Start(&dsp);
}

void dsp_term()
{
	dsp.Stopped = 1;
}

void dsp_step()
{
	AICADSP_Step(&dsp);
}

void dsp_writenmem(u32 addr)
{
	if (addr >= 0x3400 && addr < 0x3C00)
	{
		AICADSP_Start(&dsp);
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

#endif

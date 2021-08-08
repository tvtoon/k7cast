#pragma once
#include "types.h"

struct dsp_t
{
	//Dynarec
	u8 DynCode[4096*8];	//32 kb, 8 pages

	//buffered DSP state
	//24 bit wide
	s32 TEMP[128];
	//24 bit wide
	s32 MEMS[32];
	//20 bit wide
	s32 MIXS[16];
	
	//RBL/RBP (decoded)
	u32 RBP;
	u32 RBL;

	struct
	{
		bool MAD_OUT;
		bool MEM_ADDR;
		bool MEM_RD_DATA;
		bool MEM_WT_DATA;
		bool FRC_REG;
		bool ADRS_REG;
		bool Y_REG;

		bool MDEC_CT;
		bool MWT_1;
		bool MRD_1;
		//bool MADRS;
		bool MEMS;
		bool NOFL_1;
		bool NOFL_2;

		bool TEMPS;
		bool EFREG;
	}regs_init;

	//s32 -> stored as signed extended to 32 bits
	struct
	{
		s32 MAD_OUT;
		s32 MEM_ADDR;
		s32 MEM_RD_DATA;
		s32 MEM_WT_DATA;
		s32 FRC_REG;
		s32 ADRS_REG;
		s32 Y_REG;

		u32 MDEC_CT;
		u32 MWT_1;
		u32 MRD_1;
		u32 MADRS;
		u32 NOFL_1;
		u32 NOFL_2;
	}regs;
	//DEC counter :)
	//u32 DEC;

	//various dsp regs
	signed int ACC;        //26 bit
	signed int SHIFTED;    //24 bit
	signed int B;          //26 bit
	signed int MEMVAL[4];
	signed int FRC_REG;    //13 bit
	signed int Y_REG;      //24 bit
	unsigned int ADDR;
	unsigned int ADRS_REG; //13 bit

	//Direct Mapped data :
	//COEF  *128
	//MADRS *64
	//MPRO(dsp code) *4 *128
	//EFREG *16
	//EXTS  *2

	// Interpreter flags
	bool Stopped;

	//Dynarec flags
	bool dyndirty;
};

alignas(4096) extern dsp_t dsp;

void dsp_init();
void dsp_term();
void dsp_step();
void dsp_writenmem(u32 addr);

void dsp_rec_init();
void dsp_rec_step();
void dsp_recompile();

struct _INST
{
	u8 TRA;
	bool TWT;
	u8 TWA;

	bool XSEL;
	u8 YSEL;
	u8 IRA;
	bool IWT;
	u8 IWA;

	bool EWT;
	u8 EWA;
	bool ADRL;
	bool FRCL;
	u8 SHIFT;
	bool YRL;
	bool NEGB;
	bool ZERO;
	bool BSEL;

	bool NOFL;  //MRQ set
	bool TABLE; //MRQ set
	bool MWT;   //MRQ set
	bool MRD;   //MRQ set
	u8 MASA;    //MRQ set
	bool ADREB; //MRQ set
	bool NXADR; //MRQ set
};

void DecodeInst(const u32 *IPtr, _INST *i);
u16 DYNACALL PACK(s32 val);
s32 DYNACALL UNPACK(u16 val);

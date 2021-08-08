#include <sstream>

#include "types.h"
#include "sh4_mem.h"

#include "ngen.h"
#include "sh4_core.h"

#define SHIL_MODE 1
#include "shil_canonical.h"

#define SHIL_MODE 4
#include "shil_canonical.h"

//#define SHIL_MODE 2
//#include "shil_canonical.h"

#if FEAT_SHREC != DYNAREC_NONE
#define SHIL_MODE 3
#include "shil_canonical.h"
#endif

#include "ssa.h"

void AnalyseBlock(RuntimeBlockInfo* blk)
{
	SSAOptimizer optim(blk);
	optim.Optimize();
}

std::string name_reg(Sh4RegType reg)
{
	std::stringstream ss;

	if (reg >= reg_fr_0 && reg <= reg_xf_15)
		ss << "f" << (reg - reg_fr_0);
	else if (reg <= reg_r15)
		ss << "r" << reg;
	else if (reg <= reg_r7_Bank)
		ss << "r" << (reg - reg_r0_Bank) << "b";
	else
	{
		switch (reg)
		{
		case reg_sr_T:
			ss << "sr.T";
			break;
		case reg_fpscr:
			ss << "fpscr";
			break;
		case reg_sr_status:
			ss << "sr";
			break;
		case reg_pc_dyn:
			ss << "pc_dyn";
			break;
		case reg_macl:
			ss << "macl";
			break;
		case reg_mach:
			ss << "mach";
			break;
		case reg_pr:
			ss << "pr";
			break;
		case reg_gbr:
			ss << "gbr";
			break;
		case reg_nextpc:
			ss << "pc";
			break;
		case reg_fpul:
			ss << "fpul";
			break;
		case reg_old_fpscr:
			ss << "old_fpscr";
			break;
		case reg_old_sr_status:
			ss << "old_sr_status";
			break;
		case reg_ssr:
			ss << "ssr";
			break;
		default:
			ss << "s" << reg;
			break;
		}
	}

	return ss.str();
}

static std::string dissasm_param(const shil_param& prm, bool comma)
{
	std::stringstream ss;

	if (!prm.is_null() && comma)
			ss << ", ";

	if (prm.is_imm())
	{	
		if (prm.is_imm_s8())
			ss  << (s32)prm._imm ;
		else
			ss << "0x" << std::hex << prm._imm;
	}
	else if (prm.is_reg())
	{
		ss << name_reg(prm._reg);

		if (prm.count() > 1)
		{
			ss << "v" << prm.count();
		}
		ss << "." << prm.version[0];
	}

	return ss.str();
}

std::string shil_opcode::dissasm() const
{
	std::stringstream ss;
	ss << shilop_str[op] << " " << dissasm_param(rd,false) << dissasm_param(rd2,true) << " <- " << dissasm_param(rs1,false) << dissasm_param(rs2,true) << dissasm_param(rs3,true);
	return ss.str();
}

const char* shil_opcode_name(int op)
{
	return shilop_str[op];
}

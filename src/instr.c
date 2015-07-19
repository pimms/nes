#include "instr.h"
#include "oper.h"
#include "vm.h"
#include <string.h>


const struct instr_map g_instr_map[256] =
{
	{0X00, {BRK, IMPL, &op_brk}},
	{0X01, {NO_OPER, NO_FLAG, NULL}},
	{0X02, {ORA, IND_X, op_ora}},
	{0X03, {NO_OPER, NO_FLAG, NULL}},
	{0X04, {NO_OPER, NO_FLAG, NULL}},
	{0X05, {ORA, ZPG, op_ora}},
	{0X06, {ASL, ZPG, op_asl}},
	{0X07, {NO_OPER, NO_FLAG, NULL}},
	{0X08, {PHP, IMPL, op_php}},
	{0X09, {ORA, IMM, op_ora}},
	{0X0A, {ASL, ACC, op_asl}},
	{0X0B, {NO_OPER, NO_FLAG, NULL}},
	{0X0C, {NO_OPER, NO_FLAG, NULL}},
	{0X0D, {ORA, ABS, op_ora}},
	{0X0E, {ASL, ABS, op_asl}},
	{0X0F, {NO_OPER, NO_FLAG, NULL}},
	{0X10, {BPL, REL, op_bpl}},
	{0X11, {ORA, IND_Y, op_ora}},
	{0X12, {NO_OPER, NO_FLAG, NULL}},
	{0X13, {NO_OPER, NO_FLAG, NULL}},
	{0X14, {NO_OPER, NO_FLAG, NULL}},
	{0X15, {ORA, ZPG_X, op_ora}},
	{0X16, {ASL, ZPG_X, op_asl}},
	{0X17, {NO_OPER, NO_FLAG, NULL}},
	{0X18, {CLC, IMPL, op_clc}},
	{0X19, {ORA, ABS_Y, op_ora}},
	{0X1A, {NO_OPER, NO_FLAG, NULL}},
	{0X1B, {NO_OPER, NO_FLAG, NULL}},
	{0X1C, {NO_OPER, NO_FLAG, NULL}},
	{0X1D, {ORA, ABS_X, op_ora}},
	{0X1E, {ASL, ABS_X, op_asl}},
	{0X1F, {NO_OPER, NO_FLAG, NULL}},
	{0X20, {JSR, ABS, op_jsr}},
	{0X21, {AND, IND_X, op_and}},
	{0X22, {NO_OPER, NO_FLAG, NULL}},
	{0X23, {NO_OPER, NO_FLAG, NULL}},
	{0X24, {BIT, ZPG, op_bit}},
	{0X25, {AND, ZPG, op_and}},
	{0X26, {ROL, ZPG, op_rol}},
	{0X27, {NO_OPER, NO_FLAG, NULL}},
	{0X28, {PLP, IMPL, op_plp}},
	{0X29, {AND, IMM, op_and}},
	{0X2A, {ROL, ACC, op_rol}},
	{0X2B, {NO_OPER, NO_FLAG, NULL}},
	{0X2C, {BIT, ABS, op_bit}},
	{0X2D, {AND, ABS, op_and}},
	{0X2E, {ROL, ABS, op_rol}},
	{0X2F, {NO_OPER, NO_FLAG, NULL}},
	{0X30, {BMI, REL, op_bmi}},
	{0X31, {AND, IND_Y, op_and}},
	{0X32, {NO_OPER, NO_FLAG, NULL}},
	{0X33, {NO_OPER, NO_FLAG, NULL}},
	{0X34, {NO_OPER, NO_FLAG, NULL}},
	{0X35, {AND, ZPG_X, op_and}},
	{0X36, {ROL, ZPG_X, op_rol}},
	{0X37, {NO_OPER, NO_FLAG, NULL}},
	{0X38, {SEC, IMPL, op_sec}},
	{0X39, {AND, ABS_Y, op_and}},
	{0X3A, {NO_OPER, NO_FLAG, NULL}},
	{0X3B, {NO_OPER, NO_FLAG, NULL}},
	{0X3C, {NO_OPER, NO_FLAG, NULL}},
	{0X3D, {AND, ABS_X, op_and}},
	{0X3E, {ROL, ABS_X, op_rol}},
	{0X3F, {NO_OPER, NO_FLAG, NULL}},
	{0X40, {RTI, IMPL, op_rti}},
	{0X41, {EOR, IND_X, op_eor}},
	{0X42, {NO_OPER, NO_FLAG, NULL}},
	{0X43, {NO_OPER, NO_FLAG, NULL}},
	{0X44, {NO_OPER, NO_FLAG, NULL}},
	{0X45, {EOR, ZPG, op_eor}},
	{0X46, {LSR, ZPG, op_lsr}},
	{0X47, {NO_OPER, NO_FLAG, NULL}},
	{0X48, {PHA, IMPL, op_pha}},
	{0X49, {EOR, IMM, op_eor}},
	{0X4A, {LSR, ACC, op_lsr}},
	{0X4B, {NO_OPER, NO_FLAG, NULL}},
	{0X4C, {JMP, ABS, op_jmp}},
	{0X4D, {EOR, ABS, op_eor}},
	{0X4E, {LSR, ABS, op_lsr}},
	{0X4F, {NO_OPER, NO_FLAG, NULL}},
	{0X50, {BVC, REL, op_bvc}},
	{0X51, {EOR, IND_Y, op_eor}},
	{0X52, {NO_OPER, NO_FLAG, NULL}},
	{0X53, {NO_OPER, NO_FLAG, NULL}},
	{0X54, {NO_OPER, NO_FLAG, NULL}},
	{0X55, {EOR, ZPG_X, op_eor}},
	{0X56, {LSR, ZPG_X, op_lsr}},
	{0X57, {NO_OPER, NO_FLAG, NULL}},
	{0X58, {CLI, IMPL, op_cli}},
	{0X59, {EOR, ABS_Y, op_eor}},
	{0X5A, {NO_OPER, NO_FLAG, NULL}},
	{0X5B, {NO_OPER, NO_FLAG, NULL}},
	{0X5C, {NO_OPER, NO_FLAG, NULL}},
	{0X5D, {EOR, ABS_X, op_eor}},
	{0X5E, {LSR, ABS_X, op_lsr}},
	{0X5F, {NO_OPER, NO_FLAG, NULL}},
	{0X60, {RTS, IMPL, op_rts}},
	{0X61, {ADC, IND_X, op_adc}},
	{0X62, {NO_OPER, NO_FLAG, NULL}},
	{0X63, {NO_OPER, NO_FLAG, NULL}},
	{0X64, {NO_OPER, NO_FLAG, NULL}},
	{0X65, {ADC, ZPG, op_adc}},
	{0X66, {ROR, ZPG, op_ror}},
	{0X67, {NO_OPER, NO_FLAG, NULL}},
	{0X68, {PLA, IMPL, op_pla}},
	{0X69, {ADC, IMM, op_adc}},
	{0X6A, {ROR, ACC, op_ror}},
	{0X6B, {NO_OPER, NO_FLAG, NULL}},
	{0X6C, {JMP, IND, op_jmp}},
	{0X6D, {ADC, ABS, op_adc}},
	{0X6E, {ROR, ABS, op_ror}},
	{0X6F, {NO_OPER, NO_FLAG, NULL}},
	{0X70, {BVS, REL, op_bvs}},
	{0X71, {ADC, IND_Y, op_adc}},
	{0X72, {NO_OPER, NO_FLAG, NULL}},
	{0X73, {NO_OPER, NO_FLAG, NULL}},
	{0X74, {NO_OPER, NO_FLAG, NULL}},
	{0X75, {ADC, ZPG_X, op_adc}},
	{0X76, {ROR, ZPG_X, op_ror}},
	{0X77, {NO_OPER, NO_FLAG, NULL}},
	{0X78, {SET, IMPL, op_set}},
	{0X79, {ADC, ABS_Y, op_adc}},
	{0X7A, {NO_OPER, NO_FLAG, NULL}},
	{0X7B, {NO_OPER, NO_FLAG, NULL}},
	{0X7C, {NO_OPER, NO_FLAG, NULL}},
	{0X7D, {ADC, ABS_X, op_adc}},
	{0X7E, {ROR, ABS_X, op_ror}},
	{0X7F, {NO_OPER, NO_FLAG, NULL}},
	{0X80, {NO_OPER, NO_FLAG, NULL}},
	{0X81, {STA, IND_X, op_sta}},
	{0X82, {NO_OPER, NO_FLAG, NULL}},
	{0X83, {NO_OPER, NO_FLAG, NULL}},
	{0X84, {STY, ZPG, op_sty}},
	{0X85, {STA, ZPG, op_sta}},
	{0X86, {STX, ZPG, op_stx}},
	{0X87, {NO_OPER, NO_FLAG, NULL}},
	{0X88, {DEY, IMPL, op_dey}},
	{0X89, {NO_OPER, NO_FLAG, NULL}},
	{0X8A, {TXA, IMPL, op_txa}},
	{0X8B, {NO_OPER, NO_FLAG, NULL}},
	{0X8C, {STY, ABS, op_sty}},
	{0X8D, {STA, ABS, op_sta}},
	{0X8E, {STX, ABS, op_stx}},
	{0X8F, {NO_OPER, NO_FLAG, NULL}},
	{0X90, {BCC, REL, op_bcc}},
	{0X91, {STA, IND_Y, op_sta}},
	{0X92, {NO_OPER, NO_FLAG, NULL}},
	{0X93, {NO_OPER, NO_FLAG, NULL}},
	{0X94, {STY, ZPG_X, op_sty}},
	{0X95, {STA, ZPG_X, op_sta}},
	{0X96, {STX, ZPG_Y, op_stx}},
	{0X97, {NO_OPER, NO_FLAG, NULL}},
	{0X98, {TYA, IMPL, op_tya}},
	{0X99, {STA, ABS_Y, op_sta}},
	{0X9A, {TXS, IMPL, op_txs}},
	{0X9B, {NO_OPER, NO_FLAG, NULL}},
	{0X9C, {NO_OPER, NO_FLAG, NULL}},
	{0X9D, {STA, ABS_X, op_sta}},
	{0X9E, {NO_OPER, NO_FLAG, NULL}},
	{0X9F, {NO_OPER, NO_FLAG, NULL}},
	{0XA0, {LDY, IMM, op_ldy}},
	{0XA1, {LDA, IND_X, op_lda}},
	{0XA2, {LDX, IMM, op_ldx}},
	{0XA3, {NO_OPER, NO_FLAG, NULL}},
	{0XA4, {LDY, ZPG, op_ldy}},
	{0XA5, {LDA, ZPG, op_lda}},
	{0XA6, {LDX, ZPG, op_ldx}},
	{0XA7, {NO_OPER, NO_FLAG, NULL}},
	{0XA8, {TAY, IMPL, op_tay}},
	{0XA9, {LDA, IMM, op_lda}},
	{0XAA, {TAX, IMPL, op_tax}},
	{0XAB, {NO_OPER, NO_FLAG, NULL}},
	{0XAC, {LDY, ABS, op_ldy}},
	{0XAD, {LDA, ABS, op_lda}},
	{0XAE, {LDX, ABS, op_ldx}},
	{0XAF, {NO_OPER, NO_FLAG, NULL}},
	{0XB0, {BCS, REL, op_bcs}},
	{0XB1, {LDA, IND_Y, op_lda}},
	{0XB2, {NO_OPER, NO_FLAG, NULL}},
	{0XB3, {NO_OPER, NO_FLAG, NULL}},
	{0XB4, {LDY, ZPG_X, op_ldy}},
	{0XB5, {LDA, ZPG_X, op_lda}},
	{0XB6, {LDX,  ZPG_Y, op_ldx}},
	{0XB7, {NO_OPER, NO_FLAG, NULL}},
	{0XB8, {CLV, IMPL, op_clv}},
	{0XB9, {LDA, ABS_Y, op_lda}},
	{0XBA, {TSX, IMPL, op_tsx}},
	{0XBB, {NO_OPER, NO_FLAG, NULL}},
	{0XBC, {LDY, ABS_X, op_ldy}},
	{0XBD, {LDA, ABS_X, op_lda}},
	{0XBE, {LDX, ABS_Y, op_ldx}},
	{0XBF, {NO_OPER, NO_FLAG, NULL}},
	{0XC0, {CPY, IMM, op_cpy}},
	{0XC1, {CMP, IND_X, op_cmp}},
	{0XC2, {NO_OPER, NO_FLAG, NULL}},
	{0XC3, {NO_OPER, NO_FLAG, NULL}},
	{0XC4, {CPY, ZPG, op_cpy}},
	{0XC5, {CMP, ZPG, op_cmp}},
	{0XC6, {DEC, ZPG, op_dec}},
	{0XC7, {NO_OPER, NO_FLAG, NULL}},
	{0XC8, {INY, IMPL, op_iny}},
	{0XC9, {CMP, IMM, op_cmp}},
	{0XCA, {DEX, IMPL, op_dex}},
	{0XCB, {NO_OPER, NO_FLAG, NULL}},
	{0XCC, {CPY, ABS, op_cpy}},
	{0XCD, {CMP, ABS, op_cmp}},
	{0XCE, {DEC, ABS, op_dec}},
	{0XCF, {NO_OPER, NO_FLAG, NULL}},
	{0XD0, {BNE, REL, op_bne}},
	{0XD1, {CMP, IND_Y, op_cmp}},
	{0XD2, {NO_OPER, NO_FLAG, NULL}},
	{0XD3, {NO_OPER, NO_FLAG, NULL}},
	{0XD4, {NO_OPER, NO_FLAG, NULL}},
	{0XD5, {CMP, ZPG_X, op_cmp}},
	{0XD6, {DEC, ZPG_X, op_dec}},
	{0XD7, {NO_OPER, NO_FLAG, NULL}},
	{0XD8, {CLD, IMPL, op_cld}},
	{0XD9, {CMP, ABS_Y, op_cmp}},
	{0XDA, {NO_OPER, NO_FLAG, NULL}},
	{0XDB, {NO_OPER, NO_FLAG, NULL}},
	{0XDC, {NO_OPER, NO_FLAG, NULL}},
	{0XDD, {CMP, ABS_X, op_cmp}},
	{0XDE, {DEC, ABS_X, op_dec}},
	{0XDF, {NO_OPER, NO_FLAG, NULL}},
	{0XE0, {CPX, IMM, op_cpx}},
	{0XE1, {SBC, IND_X, op_sbc}},
	{0XE2, {NO_OPER, NO_FLAG, NULL}},
	{0XE3, {NO_OPER, NO_FLAG, NULL}},
	{0XE4, {CPX, ZPG, op_cpx}},
	{0XE5, {SBC, ZPG, op_sbc}},
	{0XE6, {INC, ZPG, op_inc}},
	{0XE7, {NO_OPER, NO_FLAG, NULL}},
	{0XE8, {INX, IMPL, op_inx}},
	{0XE9, {SBC, IMM, op_sbc}},
	{0XEA, {NOP, IMPL, op_nop}},
	{0XEB, {NO_OPER, NO_FLAG, NULL}},
	{0XEC, {CPX, ABS, op_cpx}},
	{0XED, {SBC, ABS, op_sbc}},
	{0XEE, {INC, ABS, op_inc}},
	{0XEF, {NO_OPER, NO_FLAG, NULL}},
	{0XF0, {BEQ, REL, op_beq}},
	{0XF1, {SBC, IND_Y, op_sbc}},
	{0XF2, {NO_OPER, NO_FLAG, NULL}},
	{0XF3, {NO_OPER, NO_FLAG, NULL}},
	{0XF4, {NO_OPER, NO_FLAG, NULL}},
	{0XF5, {SBC, ZPG_X, op_sbc}},
	{0XF6, {INC, ZPG_X, op_inc}},
	{0XF7, {NO_OPER, NO_FLAG, NULL}},
	{0XF8, {SED, IMPL, op_sed}},
	{0XF9, {SBC, ABS_Y, op_sbc}},
	{0XFA, {NO_OPER, NO_FLAG, NULL}},
	{0XFB, {NO_OPER, NO_FLAG, NULL}},
	{0XFC, {NO_OPER, NO_FLAG, NULL}},
	{0XFD, {SBC, ABS_X, op_sbc}},
	{0XFE, {INC, ABS_X, op_inc}},
	{0XFF, {NO_OPER, NO_FLAG, NULL}},
};

bool is_big_endian()
{
	int test = 1;
	uint8_t *array = (uint8_t*)&test;
	return array[0] == 0;
}

bool is_little_endian()
{
	return !is_big_endian();
}

struct iparam get_op_param(struct nes_vm *vm)
{
	struct iparam param;
	const struct instr *instr;
	int num_bytes;
	int i;

	memset(&param, 0, sizeof(param));

	instr = &g_instr_map[vm->mem[vm->pc]].instr;
	if (instr->operation == NO_OPER) {
		return param;
	}

	num_bytes = instr_byte_count(instr);

	// "num_bytes" holds the total count, including the
	// opcode itself, which must be excluded.
	for (i = 1; i < num_bytes; i++) {
		param.val[i-1] = vm->mem[vm->pc + i];
	}

	const uint16_t pval = iparam_get_val16(&param);

	if (instr->flags == ABS) {
		param.memptr = &vm->mem[pval];
	} else if (instr->flags == ABS_X) {
		param.memptr = &vm->mem[pval + vm->ix];
	} else if (instr->flags == ABS_Y) {
		param.memptr = &vm->mem[pval + vm->iy];
	}

	if (instr->flags == ZPG) {
		param.memptr = &vm->mem[pval & 0xFF];
	} else if (instr->flags == ZPG_X) {
		param.memptr = &vm->mem[(pval + vm->ix) & 0xFF];
	} else if (instr->flags == ZPG_Y) {
		param.memptr = &vm->mem[(pval + vm->iy) & 0xFF];
	}

	if (instr->flags == REL) {
		param.memptr = &vm->mem[(pval-2) & 0xFF];
	}

	if (instr->flags == IND) {
		uint16_t location = sysendian16(&vm->mem[pval]);
		param.memptr = &vm->mem[location];
	} else if (instr->flags == IND_X) {
		uint16_t zpg_ptr = (pval & 0xFF) + vm->ix;
		uint16_t location = sysendian16(&vm->mem[zpg_ptr]);
		param.memptr = &vm->mem[location];
	} else if (instr->flags == IND_Y) {
		uint16_t zpg_ptr = (pval & 0xFF);
		uint16_t location = sysendian16(&zpg_ptr);
		param.memptr = &vm->mem[location];
	}

	// Set the arithmetic literal
	if (param.memptr != NULL) {
		param.arith_lit = *param.memptr;
	} else {
		param.arith_lit = param.val[0];
	}

	return param;
}

uint16_t iparam_get_val16(const struct iparam *param)
{
	uint16_t val = 0;

	if (is_big_endian()) {
		val = param->val[1];
		val <<= 8;
		val += param->val[0];
	} else {
		val = (uint16_t)param->val;
	}

	return val;
}

uint16_t sysendian16(void *ptr)
{
	uint16_t u16;

	if (is_little_endian()) {
		u16 = *((uint16_t*)ptr);
	} else {
		uint8_t *p = (uint8_t*)&u16;
		p[0] = ((uint8_t*)(ptr))[1];
		p[1] = ((uint8_t*)(ptr))[0];
	}

	return u16;
}

const char* instr_flag_to_a(enum instr_flag flag)
{
	switch (flag) {
		case NO_FLAG:
			return "NO_FLAG";
		case ACC:
			return "ACC";
		case ABS:
			return "ABS";
		case ABS_X:
			return "ABS_X";
		case ABS_Y:
			return "ABS_Y";
		case IMM:
			return "IMM";
		case IMPL:
			return "IMPL";
		case IND:
			return "IND";
		case IND_X:
			return "IND_X";
		case IND_Y:
			return "IND_Y";
		case REL:
			return "REL";
		case ZPG:
			return "ZPG";
		case ZPG_X:
			return "ZPG_X";
		case ZPG_Y:
			return "ZPG_Y";
	}
}

const char* instr_oper_to_a(enum instr_oper oper)
{
	switch (oper) {
		case NO_OPER:
			return "NO_OPER";
		case ADC:
			return "ADC";
		case AND:
			return "AND";
		case ASL:
			return "ASL";
		case BCC:
			return "BCC";
		case BCS:
			return "BCS";
		case BEQ:
			return "BEQ";
		case BIT:
			return "BIT";
		case BMI:
			return "BMI";
		case BNE:
			return "BNE";
		case BPL:
			return "BPL";
		case BRK:
			return "BRK";
		case BVC:
			return "BVC";
		case BVS:
			return "BVS";
		case CLC:
			return "CLC";
		case CLD:
			return "CLD";
		case CLI:
			return "CLI";
		case CLV:
			return "CLV";
		case CMP:
			return "CMP";
		case CPX:
			return "CPX";
		case CPY:
			return "CPY";
		case DEC:
			return "DEC";
		case DEX:
			return "DEX";
		case DEY:
			return "DEY";
		case EOR:
			return "EOR";
		case INC:
			return "INC";
		case INX:
			return "INX";
		case INY:
			return "INY";
		case JMP:
			return "JMP";
		case JSR:
			return "JSR";
		case LDA:
			return "LDA";
		case LDX:
			return "LDX";
		case LDY:
			return "LDY";
		case LSR:
			return "LSR";
		case NOP:
			return "NOP";
		case ORA:
			return "ORA";
		case PHA:
			return "PHA";
		case PHP:
			return "PHP";
		case PLA:
			return "PLA";
		case PLP:
			return "PLP";
		case ROL:
			return "ROL";
		case ROR:
			return "ROR";
		case RTI:
			return "RTI";
		case RTS:
			return "RTS";
		case SBC:
			return "SBC";
		case SEC:
			return "SEC";
		case SED:
			return "SED";
		case SEI:
			return "SEI";
		case SET:
			return "SET";
		case STA:
			return "STA";
		case STX:
			return "STX";
		case STY:
			return "STY";
		case TAX:
			return "TAX";
		case TAY:
			return "TAY";
		case TSX:
			return "TSX";
		case TXA:
			return "TXA";
		case TXS:
			return "TXS";
		case TYA:
			return "TYA";
	}
}

enum instr_flag a_to_instr_flag(const char *str)
{
	if (strcmp("NO_FLAG", str) == 0)
		return NO_FLAG;
	if (strcmp("ACC", str) == 0)
		return ACC;
	if (strcmp("ABS", str) == 0)
		return ABS;
	if (strcmp("ABS_X", str) == 0)
		return ABS_X;
	if (strcmp("ABS_Y", str) == 0)
		return ABS_Y;
	if (strcmp("IMM", str) == 0)
		return IMM;
	if (strcmp("IMPL", str) == 0)
		return IMPL;
	if (strcmp("IND", str) == 0)
		return IND;
	if (strcmp("IND_X", str) == 0)
		return IND_X;
	if (strcmp("IND_Y", str) == 0)
		return IND_Y;
	if (strcmp("REL", str) == 0)
		return REL;
	if (strcmp("ZPG", str) == 0)
		return ZPG;
	if (strcmp("ZPG_X,", str) == 0)
		return ZPG_X;
	if (strcmp("ZPG_Y", str) == 0)
		return ZPG_Y;
	return NO_FLAG;
}

enum instr_oper a_to_instr_oper(const char *str)
{
	if (strcmp("ADC", str) == 0)
		return ADC;
	if (strcmp("AND", str) == 0)
		return AND;
	if (strcmp("ASL", str) == 0)
		return ASL;
	if (strcmp("BCC", str) == 0)
		return BCC;
	if (strcmp("BCS", str) == 0)
		return BCS;
	if (strcmp("BEQ", str) == 0)
		return BEQ;
	if (strcmp("BIT", str) == 0)
		return BIT;
	if (strcmp("BMI", str) == 0)
		return BMI;
	if (strcmp("BNE", str) == 0)
		return BNE;
	if (strcmp("BPL", str) == 0)
		return BPL;
	if (strcmp("BRK", str) == 0)
		return BRK;
	if (strcmp("BVC", str) == 0)
		return BVC;
	if (strcmp("BVS", str) == 0)
		return BVS;
	if (strcmp("CLC", str) == 0)
		return CLC;
	if (strcmp("CLD", str) == 0)
		return CLD;
	if (strcmp("CLI", str) == 0)
		return CLI;
	if (strcmp("CLV", str) == 0)
		return CLV;
	if (strcmp("CMP", str) == 0)
		return CMP;
	if (strcmp("CPX", str) == 0)
		return CPX;
	if (strcmp("CPY", str) == 0)
		return CPY;
	if (strcmp("DEC", str) == 0)
		return DEC;
	if (strcmp("DEX", str) == 0)
		return DEX;
	if (strcmp("DEY", str) == 0)
		return DEY;
	if (strcmp("EOR", str) == 0)
		return EOR;
	if (strcmp("INC", str) == 0)
		return INC;
	if (strcmp("INX", str) == 0)
		return INX;
	if (strcmp("INY", str) == 0)
		return INY;
	if (strcmp("JMP", str) == 0)
		return JMP;
	if (strcmp("JSR", str) == 0)
		return JSR;
	if (strcmp("LDA", str) == 0)
		return LDA;
	if (strcmp("LDX", str) == 0)
		return LDX;
	if (strcmp("LDY", str) == 0)
		return LDY;
	if (strcmp("LSR", str) == 0)
		return LSR;
	if (strcmp("NOP", str) == 0)
		return NOP;
	if (strcmp("ORA", str) == 0)
		return ORA;
	if (strcmp("PHA", str) == 0)
		return PHA;
	if (strcmp("PHP", str) == 0)
		return PHP;
	if (strcmp("PLA", str) == 0)
		return PLA;
	if (strcmp("PLP", str) == 0)
		return PLP;
	if (strcmp("ROL", str) == 0)
		return ROL;
	if (strcmp("ROR", str) == 0)
		return ROR;
	if (strcmp("RTI", str) == 0)
		return RTI;
	if (strcmp("RTS", str) == 0)
		return RTS;
	if (strcmp("SBC", str) == 0)
		return SBC;
	if (strcmp("SEC", str) == 0)
		return SEC;
	if (strcmp("SED", str) == 0)
		return SED;
	if (strcmp("SEI", str) == 0)
		return SEI;
	if (strcmp("SET", str) == 0)
		return SET;
	if (strcmp("STA", str) == 0)
		return STA;
	if (strcmp("STX", str) == 0)
		return STX;
	if (strcmp("STY", str) == 0)
		return STY;
	if (strcmp("TAX", str) == 0)
		return TAX;
	if (strcmp("TAY", str) == 0)
		return TAY;
	if (strcmp("TSX", str) == 0)
		return TSX;
	if (strcmp("TXA", str) == 0)
		return TXA;
	if (strcmp("TXS", str) == 0)
		return TXS;
	if (strcmp("TYA", str) == 0)
		return TYA;

	return NO_OPER;
}

int instr_byte_count(const struct instr *instr)
{
	switch (instr->flags) {
		case ABS:
		case ABS_X:
		case ABS_Y:
		case IND:
			return 3;

		case IMM:
		case IND_X:
		case IND_Y:
		case REL:
		case ZPG:
		case ZPG_X:
		case ZPG_Y:
			return 2;

		case NO_FLAG:
		case IMPL:
		case ACC:
		default:
			return 1;
	}
}

int opcode_byte_count(uint8_t opcode)
{
	return instr_byte_count(&g_instr_map[opcode].instr);
}


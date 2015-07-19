/**
 * 6502 Instruction Set
 */
#ifndef NES_INSTR_H_
#define NES_INSTR_H_

#include <stdint.h>
#include <stdbool.h>


struct nes_vm;   // Declared in vm.h
struct instr;
typedef void(*oper_func)(struct nes_vm*, const struct instr*);

enum instr_flag
{
	NO_FLAG,// Absolutely no parameters
	IMPL,	// No parameters
	ACC,	// No parameters (operate on ACC register)
	ABS,	// 16 bit (mem ref)
	ABS_X,  // 16 bit (mem ref)
	ABS_Y,  // 16 bit (mem ref)
	IMM,	// 8 bit constant
	IND,	// 16 bit (f(x) operates on *x and *(x+1))
	IND_X,	// 8 bit
	IND_Y,  // 8 bit
	REL,	// 8 bit (memory offset)
	ZPG,	// 8 bit
	ZPG_X,	// 8 bit
	ZPG_Y,  // 8 bit
};

enum instr_oper
{
	NO_OPER,
	ADC,
	AND,
	ASL,
	BCC,
	BCS,
	BEQ,
	BIT,
	BMI,
	BNE,
	BPL,
	BRK,
	BVC,
	BVS,
	CLC,
	CLD,
	CLI,
	CLV,
	CMP,
	CPX,
	CPY,
	DEC,
	DEX,
	DEY,
	EOR,
	INC,
	INX,
	INY,
	JMP,
	JSR,
	LDA,
	LDX,
	LDY,
	LSR,
	NOP,
	ORA,
	PHA,
	PHP,
	PLA,
	PLP,
	ROL,
	ROR,
	RTI,
	RTS,
	SBC,
	SEC,
	SED,
	SEI,
	SET,
	STA,
	STX,
	STY,
	TAX,
	TAY,
	TSX,
	TXA,
	TXS,
	TYA,
};

struct instr
{
	enum instr_oper operation;
	enum instr_flag flags;
	oper_func func;
};

/**
 * Parameter for an instruction.
 */
struct iparam
{
	/*
	 * val contains up to two bytes of parameters.
	 * The flags of the operation defines which elements
	 * of "val" holds valid values. When both elements
	 * are filled, the value can be retrieved endian
	 * safe using "iparam_get_val16()".
	 *
	 * As the 6502 is little endian, the first element of
	 * "val" will be the least significant with 16 bit
	 * parameters.
	 */
	uint8_t val[2];

	/*
	 * Depending on the flags of the instruction (see
	 * enum instr_flag), the memptr may point to the
	 * specified location in the VM's memory.
	 *
	 * Content, according to flag type:
	 * 	ABS, ABS_X, ABS_Y, ZPG, ZPG_X, ZPG_Y:
	 *		The location being referenced by the parameter,
	 *		added with X or Y if applicable.
	 *	REL:
	 *		The location, relative to the PC register.
	 *	IND:
	 *		The doubly-dereferenced location.
	 * 	IND_X:
	 * 		The location of the parameter added with the
	 * 		X register.
	 * 	IND_Y:
	 * 		The value of the location of the parameter, added
	 * 		with the Y register.
	 *	IMM:
	 *		NULL
	 */
	uint8_t *memptr;
};

bool is_big_endian();
bool is_little_endian();

/**
 * Retrieve the parameters of the current instructon.
 * It is expected that the PC register points to an
 * actual operation.
 */
struct iparam get_op_param(struct nes_vm*);
uint16_t iparam_get_val16(const struct iparam*);

/**
 * Converts the first two bytes at the location of "ptr" to
 * the system-endian. The data pointed to by "ptr" is expected
 * to be of little endian.
 */
uint16_t sysendian16(void *ptr);

const char *instr_flag_to_a(enum instr_flag);
const char *instr_oper_to_a(enum instr_oper);
enum instr_flag a_to_instr_flag(const char*);
enum instr_oper a_to_instr_oper(const char*);

/**
 * x_byte_count:
 * The total length of an operation, including parameters.
 */
int instr_byte_count(const struct instr *instr);
int opcode_byte_count(uint8_t opcode);

struct instr_map
{
	uint8_t code;
	struct instr instr;
};

extern const struct instr_map g_instr_map[256];


#endif

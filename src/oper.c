#include "oper.h"
#include "instr.h"
#include "vm.h"

#include <memory.h>


static void gen_op_ld(struct nes_vm *vm, uint8_t *reg)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	*reg = m;

	if (*reg == 0)
		vm->status |= STATUS_ZERO;
	if ((*reg & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

static void gen_op_transf(uint8_t *status, uint8_t *src, uint8_t *dst)
{
	*dst = *src;

	if (*dst == 0)
		*status |= STATUS_ZERO;
	if ((*dst & 0x80) != 0)
		*status |= STATUS_NEGATIVE;
}

static void gen_op_cmp(struct nes_vm *vm, uint8_t reg, uint8_t m)
{
	const uint8_t diff = reg - m;

	vm->status |= STATUS_CARRY * (reg >= m);
	vm->status |= STATUS_ZERO * (reg == m);
	vm->status |= STATUS_NEGATIVE * ((diff & 0x80) != 0);
}

static void gen_branch(struct nes_vm *vm)
{
	struct iparam param = get_op_param(vm);
	int16_t base;
	int8_t offset;

	memcpy(&base, &vm->pc, sizeof(base));
	memcpy(&offset, &param.val[0], sizeof(offset));

	base += offset;
	memcpy(&vm->pc, &base, sizeof(base));
}

static void gen_push(struct nes_vm *vm, uint8_t val)
{
	uint16_t addr = STACK_BEGIN + vm->sp;
	vm->mem[addr] = val;
	vm->sp--;
}

static void gen_pull(struct nes_vm *vm, uint8_t *dst)
{
	uint16_t addr = STACK_BEGIN + vm->sp;
	*dst = vm->mem[addr];
	vm->sp++;
}


/* Load/Store Operations */
void op_lda(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_ld(vm, &vm->acc);
}

void op_ldx(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_ld(vm, &vm->ix);
}

void op_ldy(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_ld(vm, &vm->iy);
}


void op_sta(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	*param.memptr = vm->acc;
}

void op_stx(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	*param.memptr = vm->ix;
}

void op_sty(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	*param.memptr = vm->iy;
}



/* Transfer Operations */
void op_tax(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_transf(&vm->status, &vm->acc, &vm->ix);
}

void op_tay(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_transf(&vm->status, &vm->acc, &vm->iy);
}

void op_txa(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_transf(&vm->status, &vm->ix, &vm->acc);
}

void op_tya(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_transf(&vm->status, &vm->iy, &vm->acc);
}

void op_tsx(struct nes_vm *vm, const struct instr *instr)
{
	gen_op_transf(&vm->status, &vm->sp, &vm->ix);
}

void op_txs(struct nes_vm *vm, const struct instr *instr)
{
	vm->sp = vm->ix;
}



/* Stack Operations */
void op_pha(struct nes_vm *vm, const struct instr *instr)
{
	gen_push(vm, vm->acc);
}

void op_php(struct nes_vm *vm, const struct instr *instr)
{
	gen_push(vm, vm->status);
}

void op_pla(struct nes_vm *vm, const struct instr *instr)
{
	gen_pull(vm, &vm->acc);

	if (vm->acc == 0)
		vm->status |= STATUS_ZERO;
	if ((vm->acc & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

void op_plp(struct nes_vm *vm, const struct instr *instr)
{
	gen_pull(vm, &vm->status);
}



/* Logical Operations */
void op_and(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	vm->acc &= m;

	vm->status |= STATUS_ZERO * (vm->acc == 0);
	vm->status |= STATUS_NEGATIVE * ((vm->acc & 0x80) != 0);
}

void op_eor(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	vm->acc ^= m;

	vm->status |= STATUS_ZERO * (vm->acc == 0);
	vm->status |= STATUS_NEGATIVE * ((vm->acc & 0x80) != 0);
}

void op_ora(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	vm->acc |= m;

	vm->status |= STATUS_ZERO * (vm->acc == 0);
	vm->status |= STATUS_NEGATIVE * ((vm->acc & 0x80) != 0);
}

void op_bit(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	// N and V are copied from M
	vm->status |= (m & 0xC0);

	// Z is set if (ACC & M) == 0
	if ((vm->acc & m) == 0)
		vm->status |= STATUS_ZERO;
}



/* Arithmetic Operations */
void op_adc(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	const uint16_t sum = m + vm->acc + (vm->status & STATUS_CARRY);
	vm->acc = sum & 0xFF;

	vm->status |= STATUS_ZERO * (vm->acc == 0);
	vm->status |= STATUS_OVERFLOW * ((uint16_t)vm->acc != sum);
	if (vm->acc & 0x80) {
		vm->status |= STATUS_NEGATIVE;
	}
}

void op_sbc(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;

	const uint16_t sum = vm->acc - m - !(vm->status & STATUS_CARRY);
	vm->acc = sum & 0xFF;

	vm->status |= STATUS_ZERO * (vm->acc == 0);
	vm->status |= STATUS_OVERFLOW * ((uint16_t)vm->acc != sum);
	if (vm->acc & 0x80) {
		vm->status |= STATUS_NEGATIVE;
	}
}

void op_cmp(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;
	gen_op_cmp(vm, vm->acc, m);
}

void op_cpx(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;
	gen_op_cmp(vm, vm->ix, m);
}

void op_cpy(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint8_t m = param.arith_lit;
	gen_op_cmp(vm, vm->iy, m);
}



/* Incremental and Decremental Operations */
void op_inc(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	(*param.memptr)++;

	if (*param.memptr == 0)
		vm->status |= STATUS_ZERO;
	if ((*param.memptr & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

void op_inx(struct nes_vm *vm, const struct instr *instr)
{
	vm->ix++;

	if (vm->ix == 0)
		vm->status |= STATUS_ZERO;
	if ((vm->ix & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

void op_iny(struct nes_vm *vm, const struct instr *instr)
{
	vm->iy++;

	if (vm->iy == 0)
		vm->status |= STATUS_ZERO;
	if ((vm->iy & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

void op_dec(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	(*param.memptr)--;

	if (*param.memptr == 0)
		vm->status |= STATUS_ZERO;
	if ((*param.memptr & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

void op_dex(struct nes_vm *vm, const struct instr *instr)
{
	vm->ix--;

	if (vm->ix == 0)
		vm->status |= STATUS_ZERO;
	if ((vm->ix & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}

void op_dey(struct nes_vm *vm, const struct instr *instr)
{
	vm->iy--;

	if (vm->iy == 0)
		vm->status |= STATUS_ZERO;
	if ((vm->iy & 0x80) != 0)
		vm->status |= STATUS_NEGATIVE;
}



/* Shift Operations */
void op_asl(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	uint8_t *m;

	if (instr->flags == ACC) {
		m = &vm->acc;
	} else {
		m = param.memptr;
	}

	// Copy bit 7 of "m" into V
	if ((*m & 0x80) != 0)
		vm->status |= STATUS_OVERFLOW;
	else
		vm->status &= ~STATUS_OVERFLOW;

	*m <<= 1;

	vm->status |= STATUS_ZERO * (*m == 0);
	vm->status |= STATUS_NEGATIVE * ((*m & 0x80) != 0);
}

void op_lsr(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	uint8_t *m;

	if (instr->flags == ACC) {
		m = &vm->acc;
	} else {
		m = param.memptr;
	}

	// Copy bit 0 of "m" into V
	if ((*m & 0x01) != 0)
		vm->status |= STATUS_OVERFLOW;
	else
		vm->status &= ~STATUS_OVERFLOW;

	*m >>= 1;

	vm->status |= STATUS_ZERO * (*m == 0);
	vm->status |= STATUS_NEGATIVE * ((*m & 0x80) != 0);
}

void op_rol(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	uint8_t *m;

	if (instr->flags == ACC) {
		m = &vm->acc;
	} else {
		m = param.memptr;
	}

	// store the old bit 7
	const uint8_t carry = (*m & 0x80) != 0;

	*m <<= 1;

	// Copy the old carry flag to bit 0
	if ((vm->status & STATUS_CARRY) != 0) {
		*m |= 0x01;
	}

	// Copy the old bit 7 into the carry flag
	if (carry) {
		vm->status |= STATUS_CARRY;
	} else {
		vm->status &= ~STATUS_CARRY;
	}

	vm->status |= STATUS_ZERO * (*m == 0);
	vm->status |= STATUS_NEGATIVE * ((*m & 0x80) != 0);
}

void op_ror(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	uint8_t *m;

	if (instr->flags == ACC) {
		m = &vm->acc;
	} else {
		m = param.memptr;
	}

	// Store the old bit 0
	const uint8_t carry = (*m & 0x01) != 0;

	*m >>= 1;

	// Copy the old carry flag to bit 7
	if ((vm->status & STATUS_CARRY) != 0) {
		*m |= 0x80;
	}

	// Copy the old bit 0 into the carry flag
	if (carry) {
		vm->status |= STATUS_CARRY;
	} else {
		vm->status &= ~STATUS_CARRY;
	}

	vm->status |= STATUS_ZERO * (*m == 0);
	vm->status |= STATUS_NEGATIVE * ((*m & 0x80) != 0);
}



/* Jump and Call Operations */
void op_jmp(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	uint16_t vaddr;
	vaddr = iparam_get_val16(&param);

	if (instr->flags == IND) {
		vaddr = sysendian16(&vm->mem[vaddr]);
	}

	vm->pc = vaddr;
}

void op_jsr(struct nes_vm *vm, const struct instr *instr)
{
	const struct iparam param = get_op_param(vm);
	const uint16_t addr = iparam_get_val16(&param);

	/* JSR shall push the return address (minus one) onto the stack.
	 * As JSR is a 3-byte instruction, and I assume that the next
	 * instruction is the return point, I interpret this to mean
	 * that pushing "PC + 2" is valid. This is likely because upon
	 * returning, the RTS instruction's increment (1) is added after
	 * the PC has been pulled from the stack, causing the PC to
	 * contain a valid value.
	 */
	uint16_t pc = vm->pc + 2;
	uint8_t *pcptr = (uint8_t*)&pc;

	/* I assume that I can push the 16 bit PC without taking
	 * endianness into account.
	 */
	gen_push(vm, vm->status);
	gen_push(vm, pcptr[0]);
	gen_push(vm, pcptr[1]);

	vm->pc = addr;
}

void op_rts(struct nes_vm *vm, const struct instr *instr)
{
	uint16_t pc;
	uint8_t *pcptr = (uint8_t*)&pc;

	gen_pull(vm, &pcptr[1]);
	gen_pull(vm, &pcptr[0]);
	gen_pull(vm, &vm->status);

	vm->pc = pc;
}



/* Branch Operations */
void op_bcc(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_CARRY) == 0)
		gen_branch(vm);
}

void op_bcs(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_CARRY) != 0)
		gen_branch(vm);
}

void op_beq(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_ZERO) != 0)
		gen_branch(vm);
}

void op_bne(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_ZERO) == 0)
		gen_branch(vm);
}

void op_bmi(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_NEGATIVE) != 0)
		gen_branch(vm);
}

void op_bpl(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_NEGATIVE) == 0)
		gen_branch(vm);
}

void op_bvc(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_OVERFLOW) == 0)
		gen_branch(vm);
}

void op_bvs(struct nes_vm *vm, const struct instr *instr)
{
	if ((vm->status & STATUS_OVERFLOW) != 0)
		gen_branch(vm);
}



/* Status Flag Operations */
void op_clc(struct nes_vm *vm, const struct instr *instr)
{
	vm->status &= (~STATUS_CARRY);
}

void op_cld(struct nes_vm *vm, const struct instr *instr)
{
	vm->status &= (~STATUS_DECMODE);
}

void op_cli(struct nes_vm *vm, const struct instr *instr)
{
	vm->status &= (~STATUS_INTDIS);
}

void op_clv(struct nes_vm *vm, const struct instr *instr)
{
	vm->status &= (~STATUS_OVERFLOW);
}

void op_sec(struct nes_vm *vm, const struct instr *instr)
{
	vm->status |= STATUS_CARRY;
}

void op_sed(struct nes_vm *vm, const struct instr *instr)
{
	vm->status |= STATUS_DECMODE;
}

void op_sei(struct nes_vm *vm, const struct instr *instr)
{
	vm->status |= STATUS_INTDIS;
}


/* System Operations */
void op_brk(struct nes_vm *vm, const struct instr *instr)
{ }

void op_nop(struct nes_vm *vm, const struct instr *instr)
{
	/* Max chillax :-) */
}

void op_rti(struct nes_vm *vm, const struct instr *instr)
{ }


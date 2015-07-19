#include "oper.h"
#include "instr.h"
#include "vm.h"



/* Load/Store Operations */
void op_lda(struct nes_vm *vm, const struct instr *instr)
{

}

void op_ldx(struct nes_vm *vm, const struct instr *instr)
{

}

void op_ldy(struct nes_vm *vm, const struct instr *instr)
{

}


void op_sta(struct nes_vm *vm, const struct instr *instr)
{

}

void op_stx(struct nes_vm *vm, const struct instr *instr)
{

}

void op_sty(struct nes_vm *vm, const struct instr *instr)
{

}



/* Transfer Operations */
void op_tax(struct nes_vm *vm, const struct instr *instr)
{

}

void op_tay(struct nes_vm *vm, const struct instr *instr)
{

}

void op_txa(struct nes_vm *vm, const struct instr *instr)
{

}

void op_tya(struct nes_vm *vm, const struct instr *instr)
{

}



/* Stack Operations */
void op_tsx(struct nes_vm *vm, const struct instr *instr)
{

}

void op_txs(struct nes_vm *vm, const struct instr *instr)
{

}

void op_pha(struct nes_vm *vm, const struct instr *instr)
{

}

void op_php(struct nes_vm *vm, const struct instr *instr)
{

}

void op_pla(struct nes_vm *vm, const struct instr *instr)
{

}

void op_plp(struct nes_vm *vm, const struct instr *instr)
{

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

}

void op_cpx(struct nes_vm *vm, const struct instr *instr)
{

}

void op_cpy(struct nes_vm *vm, const struct instr *instr)
{

}

void op_set(struct nes_vm *vm, const struct instr *instr)
{

}



/* Incremental and Decremental Operations */
void op_inc(struct nes_vm *vm, const struct instr *instr)
{

}

void op_inx(struct nes_vm *vm, const struct instr *instr)
{

}

void op_iny(struct nes_vm *vm, const struct instr *instr)
{

}

void op_dec(struct nes_vm *vm, const struct instr *instr)
{

}

void op_dex(struct nes_vm *vm, const struct instr *instr)
{

}

void op_dey(struct nes_vm *vm, const struct instr *instr)
{

}



/* Shift Operations */
void op_asl(struct nes_vm *vm, const struct instr *instr)
{

}

void op_lsr(struct nes_vm *vm, const struct instr *instr)
{

}

void op_rol(struct nes_vm *vm, const struct instr *instr)
{

}

void op_ror(struct nes_vm *vm, const struct instr *instr)
{

}



/* Jump and Call Operations */
void op_jmp(struct nes_vm *vm, const struct instr *instr)
{

}

void op_jsr(struct nes_vm *vm, const struct instr *instr)
{

}

void op_rts(struct nes_vm *vm, const struct instr *instr)
{

}



/* Branch Operations */
void op_bcc(struct nes_vm *vm, const struct instr *instr)
{

}

void op_bcs(struct nes_vm *vm, const struct instr *instr)
{

}

void op_beq(struct nes_vm *vm, const struct instr *instr)
{

}

void op_bmi(struct nes_vm *vm, const struct instr *instr)
{

}

void op_bne(struct nes_vm *vm, const struct instr *instr)
{

}

void op_bpl(struct nes_vm *vm, const struct instr *instr)
{

}

void op_bvc(struct nes_vm *vm, const struct instr *instr)
{

}

void op_bvs(struct nes_vm *vm, const struct instr *instr)
{

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
{

}

void op_nop(struct nes_vm *vm, const struct instr *instr)
{

}

void op_rti(struct nes_vm *vm, const struct instr *instr)
{

}


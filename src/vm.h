/**
 * 6502 Virtual Machine
 */
#ifndef NES_VM_H_
#define NES_VM_H_

#include <inttypes.h>

#define STATUS_CARRY 	0x01
#define STATUS_ZERO		0x02
#define STATUS_INTDIS	0x04
#define STATUS_DECMODE	0x08
#define STATUS_BREAK    0x10
#define STATUS_OVERFLOW 0x40
#define STATUS_NEGATIVE 0x80

#define STACK_BEGIN		0x0100
#define STACK_END		0x01FF

struct nes_vm
{
	uint16_t pc;
	uint8_t sp;
	uint8_t acc;
	uint8_t ix;
	uint8_t iy;
	uint8_t status;

	uint8_t mem[0x10000];
};

struct nes_vm* nes_create();
void nes_destroy(struct nes_vm*);


#endif

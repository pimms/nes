#include <stdlib.h>
#include <memory.h>

#include "vm.h"


struct nes_vm* nes_create()
{
	struct nes_vm *vm = malloc(sizeof(struct nes_vm));
	memset(vm, 0, sizeof(struct nes_vm));
	vm->sp = 0xFF;
	return vm;
}

void nes_destroy(struct nes_vm *vm)
{
	free(vm);
}

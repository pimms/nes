#include <stdio.h>
#include <stdlib.h>
#include "instr.h"


int main(int argc, char **argv)
{
	int i;

	if (argc == 1) {
		printf("No rom file specified.\n");
		return 0;
	}

	FILE *f = fopen(argv[1], "r");
	if (!f) {
		printf("Failed to open file '%s'\n", argv[1]);
		return 1;
	}

	for (i=0; i<128; i++) {
		uint8_t b = fgetc(f);
		struct instr instr = g_instr_map[b].instr;
		printf("%x      %s %s\n",
				i,
				instr_oper_to_a(instr.operation),
				instr_flag_to_a(instr.flags));
	}

	fclose(f);

	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/core_function.h"
//#include "../include/cpu.h"

void print_cpu_values(cpu* proc)
{
	printf("opcode: %c\nprogram_counter: %hi\nI: %hi\nsp: %hi\n", proc->opcode, proc->program_counter, proc->I, proc->sp);
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("USAGE: ./chip8 [file_name]\n");
		return -1;
	}

	char* file_path = malloc(sizeof(argv[1]));
	memcpy(file_path, argv[1], sizeof(argv[1]));

	cpu* proc = malloc(sizeof(cpu));
	init_system(proc);
	print_cpu_values(proc);

	load_program(proc, file_path);

	while(1)
	{
		cycle_emulation(proc);
	}
	free(file_path);
	free(proc);


	return 0;
}

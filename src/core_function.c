#include "../include/core_function.h"


void init_system(cpu* proc)
{
	proc->opcode = 0;

	proc->program_counter = 0x200;		

	proc->I = 0;

	proc->sp = 0;

	//Clear display
	for(int i = 0; i< 64*32; i++)
	{
		proc->screen[i] = 0;
	}

	//Set stack to zero
	for(int i = 0; i < 16; i++)
	{
		proc->stack[i] = 0;
	}

	//Zero V register
	for(int i =0; i < 16; i++)
	{
		proc->V[i] = 0;
	}

	//Zero memory
	for(int i = 0; i < 4096; i++)
	{
		proc->memory[i] = 0;
	}	
	
	//Timer to zero
	proc->delay_timer = 0;
	proc->sound_timer = 0;

	//Font set
	for(int i = 0; i < 80; i++)
	{
		proc->memory[i] = chip8_fontset[i];	
	}
}

void load_program(cpu* proc, char* file_path)
{
	FILE* prog;
	unsigned char buf[4096 - 512];


	if ((prog = fopen(file_path,"r")) == NULL)
	{
		printf("ERROR READING FILE\n");
		exit(0);
	}

	fread(buf, sizeof(buf), 1, prog);

	for(int i = 0; i < (4096 - 512); i++)
	{
		proc->memory[i+512] = buf[i];
	}


	fclose(prog);

}


void cycle_emulation(cpu* proc)
{

	//Fetch OP Code
	
	proc->opcode = proc->memory[proc->program_counter] << 8 | proc->memory[proc->program_counter + 1];
	//Decode
	
	//Execute
	
	//Update

}

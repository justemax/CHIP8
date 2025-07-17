#include "../include/instructions.h"

/*
 * Clean Screen
 */
void op_00e0(cpu* proc)
{
	for(int i = 0; i < 64*32; i++)
	{
		proc->screen[i] = 0;
	}	

}

/*
 * Return
 */
void op_00ee(cpu* proc)
{
	
}

/*
 * Jump to NNN
 */
void op_1000(cpu* proc)
{
	proc->program_counter = proc->opcode & 0x0FFF;
}

/*
 * Call subroutine NNN
 */
void op_2000(cpu* proc)
{
	proc->stack[proc->sp] = proc->program_counter;
	proc->sp ++;
	proc->program_counter = proc->opcode & 0x0FFF;
}

/*
 * Skip next instruction if V[n] == kk
 */
void op_3000(cpu* proc)
{
	char register_number = (proc->opcode >> 8) & 0xF;
	if(proc->V[register_number] == proc->opcode & 0xFF)
	{
		proc->program_counter += 2;
	}
}

/*
 * Skip next instruction if V[n] != kk
 */
void op_4000(cpu* proc)
{
	char register_number = (proc->opcode >> 8) & 0xF;
	if(proc->V[register_number] == proc->opcode & 0xFF)
	{
		proc->program_counter += 2;
	}
}
/*
 * Compare two V register
 * skip to next if equal
 */
void op_5000(cpu* proc)
{
	char register_number_x = (proc->opcode >> 4) & 0xF;
	char register_number_y = (proc->opcode >> 8) & 0xF;
	if(proc->V[register_number_x] == proc->V[register_number_y])
	{
		proc->program_counter += 2;
	}
}

/*
 * Set V register
 */
void op_6000(cpu* proc)
{
	char register_number = (proc->opcode >> 8) & 0xF;
	proc->V[register_number] = proc->opcode & 0xFF;
}

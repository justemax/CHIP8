#include "../instructions.h"

/*
 * Clean Screen
 */
void op_00e0(cpu* proc)
{
	for(int i = 0; i < 64*32; i++)
	{
		screen[i] = 0;
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
	proc->sp ++;
	proc->stack[sp] = proc->program_counter;
	proc->program_counter = proc->opcode & 0x0FFF;
}


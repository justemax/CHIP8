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
	proc->program_counter = proc->opcode & 0xFFF;
}

/*
 * Call subroutine NNN
 */
void op_2000(cpu* proc)
{
	proc->stack[proc->sp] = proc->program_counter;
	proc->sp ++;
	proc->program_counter = proc->opcode & 0xFFF;
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




/*
 * Add xx to V register
 */
void op_7000(cpu* proc)
{
	char register_number = (proc->opcode >> 8) & 0xF;
	proc->V[register_number] += proc->opcode & 0xFF;
}

//0x8XX





/*
 * Store Vx into Vy
 */
void op_8000(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_y];

}

/*
 * Vx = Vx OR Vy
 */
void op_8001(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x]  | proc->V[register_number_y];


}


/*
 * Vx = Vx AND Vy
 */
void op_8002(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x]  & proc->V[register_number_y];

}

/* 
 * Vx = Vx XOR Vy
 */
void op_8003(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x]  ^ proc->V[register_number_y];


}

/*
 * Vx = Vx + Vy
 */
void op_8004(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x] + proc->V[register_number_y];

	if((proc->V[register_number_x] + proc->V[register_number_y]) > 255)
	{
		proc->V[15] = 1;
	}


}

/*
 * Vx = Vx - Vy
 */
void op_8005(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x] - proc->V[register_number_y];

	if(proc->V[register_number_x] >  proc->V[register_number_y])
	{
		proc->V[15] = 1;
	}
}


/*
 * SHR Vx 
 */
void op_8006(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;

	if((proc->V[register_number_x] & 0x1) == 1)
	{
		proc->V[15] = 1;
	}
	proc->V[register_number_x] = proc->V[register_number_x] >> 1;
}

/*
 * Vx = Vy - Vx
 */
void op_8007(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_y] - proc->V[register_number_x];

	if(proc->V[register_number_x] <  proc->V[register_number_y])
	{
		proc->V[15] = 1;
	}
}

/*
 * SHL Vx
 */
void op_800e(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;

	if((proc->V[register_number_x] & 0x80) == 1)
	{
		proc->V[15] = 1;
	}
	proc->V[register_number_x] = proc->V[register_number_x] << 1;

}



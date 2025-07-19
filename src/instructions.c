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

	proc->program_counter += 2;
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
	proc->program_counter += 2;
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
	proc->program_counter += 2;
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
	proc->program_counter += 2;
}

/*
 * Set V register
 */
void op_6000(cpu* proc)
{
	char register_number = (proc->opcode >> 8) & 0xF;
	proc->V[register_number] = proc->opcode & 0xFF;
	proc->program_counter += 2;
}




/*
 * Add xx to V register
 */
void op_7000(cpu* proc)
{
	char register_number = (proc->opcode >> 8) & 0xF;
	proc->V[register_number] += proc->opcode & 0xFF;
	proc->program_counter += 2;
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
	proc->program_counter += 2;

}

/*
 * Vx = Vx OR Vy
 */
void op_8001(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x]  | proc->V[register_number_y];
	proc->program_counter += 2;


}


/*
 * Vx = Vx AND Vy
 */
void op_8002(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x]  & proc->V[register_number_y];
	proc->program_counter += 2;

}

/* 
 * Vx = Vx XOR Vy
 */
void op_8003(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	proc->V[register_number_x] = proc->V[register_number_x]  ^ proc->V[register_number_y];
	proc->program_counter += 2;


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

	proc->program_counter += 2;

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
	proc->program_counter += 2;
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
	proc->program_counter += 2;
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
	proc->program_counter += 2;
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
	proc->program_counter += 2;

}


/*
 * if Vx != Vy skip next instruction
 */
void op_9000(cpu* proc)
{

	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;

	if(proc->V[register_number_x] != proc->V[register_number_y])
	{
		proc->program_counter += 2;
	}
	proc->program_counter += 2;

}

/*
 * Set I register ton nnn
 */
void op_a000(cpu* proc)
{
	proc->I = proc->opcode & 0x0FFF; 
	proc->program_counter += 2;
}

/*
 * Jump to nnn + V[0]
 */
void op_b000(cpu* proc)
{
	proc->program_counter = (proc->opcode & 0x0FFF) + proc->V[0];
	proc->program_counter += 2;
}

/*
 * Set Vx = Rand AND nn
 */
void op_c000(cpu* proc)
{

	char register_number_x = (proc->opcode >> 8) & 0xF;
	char rand_number = rand() % 256;

	proc->V[register_number_x] = rand_number & (proc->opcode & 0xFF);

	proc->program_counter += 2;
}

/*
 *  Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
 */
void op_d000(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	char register_number_y = (proc->opcode >> 4) & 0xF;
	char nibble = (proc->opcode) & 0xF;

	char x = proc->V[register_number_x];
	char y = proc->V[register_number_y];

	char byte;

	for(int i = 0; i < nibble; i++)
	{
		byte = proc->memory[proc->I + i];
		for(int j = 0; j < 8; j++)
		{
			if((byte & (0x80 >> j)) != 0)
			{
				if(proc->screen[i * 64 + y] == 1)
				{
					proc->V[15] = 1;
				}
				proc->screen[i * 64 + y] = proc->screen[i * 64 + y] ^ 1;
			}
		}
	}

	proc->program_counter += 2;
}


//OxEXX
/*
 * Skip next if key[Vx]
 */
void op_e09e(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	
	if(proc->key[proc->V[register_number_x]] == 1)
	{
		proc->program_counter += 2;
	}
	proc->program_counter += 2;
}

/*
 * Skip next if not key[Vx]
 */
void op_e0a1(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;
	
	if(proc->key[proc->V[register_number_x]] != 1)
	{
		proc->program_counter += 2;
	}
	proc->program_counter += 2;
}



// OxFXX

/*
 * Set Vx to timer value
 */
void op_f007(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;

	proc->delay_timer = proc->V[register_number_x];
	proc->program_counter += 2;
}

/*
 * Store key to Vx
 */
void op_f00a(cpu* proc)
{
	
	char register_number_x = (proc->opcode >> 8) & 0xF;
	

	while(1)
	{
		for(int i = 0;  i < 8; i++)
		{
			if(proc->key[i] == 1)
			{
				proc->V[register_number_x] = i;
				proc->program_counter +=2;
				return;
			}
		}
	}
}

/*
 * Set delay timer to Vx
 */
void op_f015(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;

	proc->delay_timer = proc->V[register_number_x];

	proc->program_counter += 2;
}

/*
 * Sound timer = Vx
 */
void op_f018(cpu* proc)
{
	char register_number_x = (proc->opcode >> 8) & 0xF;

	proc->sound_timer = proc->V[register_number_x];

	proc->program_counter += 2;
}


/*
 * I = I + Vx
 */
void op_f01e(cpu* proc)
{

	char register_number_x = (proc->opcode >> 8) & 0xF;

	proc->I = proc->V[register_number_x] + proc->I;

	proc->program_counter += 2;
}

/*
 * I = Vx * 0x5 
 */
void op_f029(cpu* proc)
{

	char register_number_x = (proc->opcode >> 8) & 0xF;

	proc->I = proc->V[register_number_x] * 0x5;

	proc->program_counter += 2;
}

/*
 * Store the Binary Coded Decimal representation of Vx
 */
void op_f033(cpu* proc)
{

	char register_number_x = (proc->opcode >> 8) & 0xF;

	proc->memory[proc->I] = proc->V[register_number_x] /100;
	proc->memory[proc->I + 1] = (proc->V[register_number_x] /10) % 10;
	proc->memory[proc->I + 2] = (proc->V[register_number_x] % 100) % 10;

	proc->program_counter += 2;
}

/*
 * Store V to memory
 */
void op_f055(cpu* proc)
{
	
	char max_register = (proc->opcode >> 8) & 0xF;

	for(int i = 0; i < max_register; i++)
	{
		proc->memory[proc->I + i] = proc->V[i];
	}

	proc->program_counter += 2;


}

/*
 * Store memory to V
 */
void op_f065(cpu* proc)
{
	
	char max_register = (proc->opcode >> 8) & 0xF;

	for(int i = 0; i < max_register; i++)
	{
		proc->V[i] = proc->memory[proc->I + i];
	}

	proc->program_counter += 2;


}

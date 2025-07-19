#include "../include/core_function.h"
#include "../include/instructions.h"

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

	printf("%x \n", proc->opcode);
	//Decode
	//Execute
	switch(proc->opcode & 0xF000)
	{
		//Manage all 0x0XXX cases
		case 0x0000:
			switch(proc->opcode & 0x00FF)
			{
				case 0x00E0: //Clear screen
					op_00e0(proc);
					break;
				case 0x00EE: //Return from subroutine
					op_00ee(proc);
					break;
				default:
					printf("UNKNOWN 0x0XXX OPCODE: %x", proc->opcode);
			}

		case 0x1000: //jump to addr
			op_1000(proc);
			break;

		case 0x2000: //call subroutine
			op_2000(proc);
			break;
	
		case 0x3000:
			op_3000(proc);
			break;

		case 0x4000:
			op_4000(proc);
			break;

		case 0x5000:
			op_5000(proc);
			break;

		case 0x6000:
			op_6000(proc);
			break;

		case 0x7000:
			op_7000(proc);
			break;

		case 0x8000:
			switch(proc->opcode & 0x000F)
			{
				case 0x8001:
					op_8001(proc);
					break;

				case 0x8002:
					op_8002(proc);
					break;

				case 0x8003:
					op_8003(proc);
					break;

				case 0x8004:
					op_8004(proc);
					break;

				case 0x8005:
					op_8005(proc);
					break;

				case 0x8006:
					op_8006(proc);
					break;

				case 0x8007:
					op_8007(proc);
					break;

				case 0x800E:
					op_800e(proc);
					break;

				default:
					printf("UNKNOWN INSTRUCTION 0x8XXX: %x\n", proc->opcode);
			}

		case 0x9000:
			op_9000(proc);
			break;

		case 0xA000:
			op_a000(proc);
			break;

		case 0xB000:
			op_b000(proc);
			break;

		case 0xC000:
			op_c000(proc);
			break;

		case 0xD000:
			op_d000(proc);
			break;

		case 0xE000:
			switch(proc->opcode & 0x00FF)
			{
				case 0x009E:
					op_e09e(proc);
					break;

				case 0x00A1:
					op_e0a1(proc);
					break;

				default:
					printf("UNKNOWN INSTRUCTION 0x9XXX: %x\n", proc->opcode);
			}

		case 0xF000:
			switch(proc->opcode & 0x00FF)
			{
				case 0x0007:
					op_f007(proc);
					break;

				case 0x000A:
					op_f00a(proc);
					break;


				case 0x0015:
					op_f015(proc);
					break;


				case 0x0018:
					op_f018(proc);
					break;


				case 0x001E:
					op_f01e(proc);
					break;


				case 0x0029:
					op_f029(proc);
					break;


				case 0x0033:
					op_f033(proc);
					break;


				case 0x0055:
					op_f055(proc);
					break;


				case 0x0065:
					op_f065(proc);
					break;

				default:
					printf("UNKNOWN INSTRUCTION 0xFXXX: %x\n", proc->opcode);

			}

		default:
			printf("UNKNOWN INSTRUCTION : %x\n", proc->opcode);
			break;

	}
	

}

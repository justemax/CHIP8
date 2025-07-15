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
					break;
				case 0x00EE: //Return from subroutine
					break;
				default:
					printf("UNKNOWN 0x0XXX OPCODE: %x", proc->opcode);
			}

		case 0x1000: //jump to addr
			break;

		case 0x2000: //call subroutine
			break;
	
		case 0x3000:
			break;

		case 0x4000:
			break;

		case 0x5000:
			break;

		case 0x6000:
			break;

		case 0x7000:
			break;

		case 0x8000:
			switch(proc->opcode & 0x000F)
			{
				case 0x001:
					break;

				case 0x002:
					break;

				case 0x003:
					break;

				case 0x004:
					break;

				case 0x005:
					break;

				case 0x006:
					break;

				case 0x007:
					break;

				case 0x00E:
					break;

				default:
					printf("UNKNOWN INSTRUCTION 0x8XXX: %x\n", proc->opcode);
			}

		case 0x9000:
			break;

		case 0xA000:
			break;

		case 0xB000:
			break;

		case 0xC000:
			break;

		case 0xD000:
			break;

		case 0xE000:
			switch(proc->opcode & 0x00FF)
			{
				case 0x009E:
					break;

				case 0x00A1:
					break;

				default:
					printf("UNKNOWN INSTRUCTION 0x9XXX: %x\n", proc->opcode);
			}

		case 0xF000:
			switch(proc->opcode & 0x00FF)
			{
				case 0x0007:
					break;

				case 0x000A:
					break;


				case 0x0015:
					break;


				case 0x0018:
					break;


				case 0x001E:
					break;


				case 0x0029:
					break;


				case 0x0033:
					break;


				case 0x0055:
					break;


				case 0x0065:
					break;

				default:
					printf("UNKNOWN INSTRUCTION 0xFXXX: %x\n", proc->opcode);

			}

		default:
			printf("UNKNOWN INSTRUCTION : %x\n", proc->opcode);
			break;

	}
	
	//Update
	proc->program_counter += 2;

}

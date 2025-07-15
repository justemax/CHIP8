/* Definition of the cpu for emulation */

#pragma once

typedef struct cpu
{
	unsigned char opcode;

	//Memory definitiopn of 4096 bits
	unsigned char memory[4096];

	//Definition of V register
	unsigned char V[16];


	//Index register
	unsigned short I;

	//Program counter
	unsigned  short program_counter;


	//Screen_emulation
	unsigned char screen[64 * 32];

	//Timer
	unsigned char delay_timer;
	unsigned char sound_timer;

	//Stack and stack pointer
	unsigned short stack[16];
	unsigned short sp;

	//Keyboard
	unsigned short key[16];
} cpu;

extern const unsigned char chip8_fontset[80];

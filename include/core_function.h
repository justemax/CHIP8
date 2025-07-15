/* Core functions for CHIP8 emulation */
#pragma once
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>


void init_system(cpu* proc);

void load_program(cpu* proc, char* file_path);

void cycle_emulation(cpu* proc);

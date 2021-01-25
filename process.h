#pragma once

#include <stdint.h>
#include "queue.h"

#define NUM_PROCESSES 20
#define IO_DEVICE_NUMBER 3

enum Instruction {DISK, TAPE, PRINTER, CPU};


typedef struct Process {
    unsigned start;
    Queue* instructions;
    
    unsigned id, IOcounter;
} Process;

extern Process* process_table[];

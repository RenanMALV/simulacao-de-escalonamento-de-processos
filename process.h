#pragma once

#include "queue.h"

enum Instruction {DISK, TAPE, PRINTER, CPU};
const unsigned IO_DEVICE_NUMBER = CPU;

typedef struct Process {
    unsigned start;
    Queue* instructions;
    
    unsigned id, IOcounter;
} Process;

#include "process.h"

Process* process_table[NUM_PROCESSES] = {0};

unsigned process_count = 0;

void process_add_instructions(Process* p, enum Instruction i, int amount){
    for (;amount > 0;amount--){
        queue_push(p->instructions, i);
    }
}

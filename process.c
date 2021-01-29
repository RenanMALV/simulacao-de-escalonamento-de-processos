#include "process.h"

static Process* process_table_internal[NUM_PROCESSES] = {0};

Process** process_table = process_table_internal-1;

unsigned process_count = 0;

void process_add_instructions(Process* p, enum Instruction i, int amount){
    for (;amount > 0;amount--){
        queue_push(p->instructions, i);
    }
}

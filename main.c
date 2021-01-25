#include <stdio.h>
#include <stdint.h>

#include "process.h"
#include "queue.h"
#include "scheduler.h"



unsigned CPUtime = 0;

// Process creation
uint8_t pid_gen = 0;
int future_index = 0;
const int TOTAL_PROCESSES = 2;
Process future_processes[TOTAL_PROCESSES] = {
    {.start=0},
    {.start=5}
};

void create_processes(){
    while (future_index < TOTAL_PROCESSES){
        Process* p = &future_processes[future_index];
        if (CPUtime == p->start){
            pid_gen++;
            p->id = pid_gen;
            queue_push(ready_queues[0], pid_gen);
            process_table[pid_gen] = p;
            future_index++;
            printf("New process: %d\n", p->id);
        }
        else{
            return;
        }   
    }
}

void process_add_instructions(Process* p, enum Instruction i, int amount){
    for (;amount > 0;amount--){
        queue_push(p->instructions, i);
    }
}


int main(void){
    
    for (int i = 0; i < NUM_PRIORITIES; i++)
        ready_queues[i] = queue_create(NUM_PROCESSES);
        
    
    for (int i = 0; i < IO_DEVICE_NUMBER; i++)
        IOqueues[i] = queue_create(NUM_PROCESSES);
        
    future_processes[0].instructions = queue_create(20);
    process_add_instructions(&future_processes[0], CPU, 5);
    future_processes[1].instructions = queue_create(20);
    process_add_instructions(&future_processes[1], CPU, 5);

    while (CPUtime < 100){
        create_processes();
        
        scheduler();
        
        if (currentProcess){
            printf("%d : %d\n", CPUtime, currentProcess->id);
            timeUsed++;
        }
        CPUtime++;
        // printf("Test");
    }
}

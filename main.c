#include <stdio.h>
#include <stdint.h>

#include "process.h"
#include "queue.h"


int future_index = 0;
const int TOTAL_PROCESSES = 2;
Process future_processes[TOTAL_PROCESSES] = {
    {.start=0},
    {.start=5}
};


const uint8_t NUM_PROCESSES = 20;
const uint8_t NUM_PRIORITIES = 2;
Queue* ready_queues[NUM_PRIORITIES];


unsigned CPUtime = 0;
Process* currentProcess = NULL;

uint8_t timeUsed = 0;
const uint8_t MAX_TIMED_USED = 3;

uint8_t pid_gen = 0;

Queue* IOqueues[IO_DEVICE_NUMBER];

Process* process_table[NUM_PROCESSES] = {0};

int main(void){
    
    for (int i = 0; i < NUM_PRIORITIES; i++)
        ready_queues[i] = queue_create(NUM_PROCESSES);
        
    
    for (int i = 0; i < IO_DEVICE_NUMBER; i++)
        IOqueues[IO_DEVICE_NUMBER] = queue_create(NUM_PROCESSES);
        
    
}

void create_processes(){
    while (future_index < TOTAL_PROCESSES){
        Process p = future_processes[future_index];
        if (CPUtime == p.start){
            pid_gen++;
            p.id = pid_gen;
            queue_push(ready_queues[0], pid_gen);
            process_table[pid_gen] = &p;
        }
        else{
            return;
        }   
    }
}

void get_next_process(){
    for (int i = 0; i < NUM_PRIORITIES; i++) {
        if (!queue_isempty(ready_queues[i])) {
            currentProcess = process_table[queue_pop(ready_queues[i])];
            timeUsed = 0;
            return;
        }
    }
    currentProcess = NULL;
}

void scheduler(){
    if (!currentProcess){
        get_next_process();
    }
    else {
        if (queue_isempty(currentProcess->instructions)){
            get_next_process();
        }
        else if (timeUsed == MAX_TIMED_USED){
            queue_push(ready_queues[1], currentProcess->id);
            get_next_process();
        }
    }
    
    int instruction;
    while (currentProcess && (instruction = queue_pop(currentProcess->instructions)) == CPU){
        queue_push(IOqueues[instruction], currentProcess->id);
        currentProcess->IOcounter = 7;
        get_next_process;
    }
}

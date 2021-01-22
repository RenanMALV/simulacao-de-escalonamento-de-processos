#include <stdio.h>
#include <stdint.h>

#include "process.h"
#include "queue.h"

Process processList[2] = {
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

uint8_t PID_GEN = 0;

Queue* IOqueues[IO_DEVICE_NUMBER];

Process* process_table[NUM_PROCESSES] = {0};

int main(void){
    
    for (int i = 0; i < NUM_PRIORITIES; i++)
        ready_queues[i] = queue_create(NUM_PROCESSES);
        
    
    for (int i = 0; i < IO_DEVICE_NUMBER; i++)
        IOqueues[IO_DEVICE_NUMBER] = queue_create(NUM_PROCESSES);
        
    
}

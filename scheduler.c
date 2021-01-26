#include "scheduler.h"
#include "devices.h"

Process* currentProcess = NULL;
Queue* ready_queues[NUM_PRIORITIES];
uint8_t timeUsed = 0;

/*
 Esta função irá atribuir à global "currentProcess" o ponteiro do próximo processo
a ser executado, de acordo com a ordem das filas de prioridade.
*/
static void get_next_process(){
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
        else if (timeUsed == MAX_TIME_USED){
            queue_push(ready_queues[1], currentProcess->id);
            get_next_process();
        }
    }

    
    int instruction;
    while (currentProcess && (instruction = queue_pop(currentProcess->instructions)) != CPU){
        request_device(instruction, currentProcess->id);
        get_next_process();
    }
    
    if (currentProcess){
        timeUsed++;
    }
}

#include "scheduler.h"

// Prioridade atribuída a processos que foram preemptidos por consumirem toda sua fatia de tempo.
#define PREEMPTED_PROCESS_PRIORITY 1

static Queue* ready_queues[NUM_PRIORITIES];

/*
 Esta função irá atribuir à global "currentProcess" o ponteiro do próximo processo
a ser executado, de acordo com a ordem das filas de prioridade.
*/
static void get_next_process(){
    for (int i = 0; i < NUM_PRIORITIES; i++) {
        if (!queue_isempty(ready_queues[i])) {
            currentProcess = process_table[queue_pop(ready_queues[i])];
            timeUsed = 0;
            currentProcess->state = PSTATE_RUNNING;
            return;
        }
    }
    currentProcess = NULL;
}

// -----

Process* currentProcess = NULL;
uint8_t timeUsed = 0;

extern void schedule_process(Process* p){
    p->state = PSTATE_READY;
    queue_push(ready_queues[p->priority], p->id);
}

extern void scheduler_block(){
    currentProcess->state = PSTATE_BLOCKED;
    get_next_process();
}

extern void scheduler(){
    if (!currentProcess){
        get_next_process();
    }
    else {
        if (queue_isempty(currentProcess->instructions)){
            currentProcess->state = PSTATE_TERMINATED;
            process_count--;
            get_next_process();
        }
        else if (timeUsed >= MAX_TIME_USED){
            currentProcess->priority = PREEMPTED_PROCESS_PRIORITY;
            schedule_process(currentProcess);
            get_next_process();
        }
    }
}

extern void scheduler_init(){
    for (int i = 0; i < NUM_PRIORITIES; i++)
        ready_queues[i] = queue_create(NUM_PROCESSES);
}

#include <stdio.h>
#include "process.h"
#include "scheduler.h"
#include "creator.h"
#include "output.h"

#define TOTAL_PROCESSES  3  // Total de processos pré-definidos criados.


// Indica qual será o índice da próxima operação da CPU
static int future_index = 0;

static Process future_processes[TOTAL_PROCESSES] = {
    {.start=0},
    {.start=5},
    {.start=5}
};

// -----

extern int has_incoming_processes(){
    return future_index < TOTAL_PROCESSES;
}

extern void create_processes(){
    static uint8_t pid_gen = 0;
    
    while (future_index < TOTAL_PROCESSES){
        Process* p = &future_processes[future_index];
        if (CPUtime == p->start){
            pid_gen++;
            future_index++;
            
            // Inicializar processo
            p->id = pid_gen;
            p->state = PSTATE_CREATED;
            p->priority = INITIAL_PRIORITY;
            process_table[p->id] = p;
            output_info(p);
            process_count++;
            
            schedule_process(p);
        }
        else{
            return;
        }   
    }
}

extern void initialize_processes(){
    future_processes[0].instructions = queue_create(20);
    process_add_instructions(&future_processes[0], CPU, 3);
    process_add_instructions(&future_processes[0], DISK, 1);
    process_add_instructions(&future_processes[0], CPU, 10);
    
    future_processes[1].instructions = queue_create(20);
    process_add_instructions(&future_processes[1], CPU, 5);
    
    future_processes[2].instructions = queue_create(20);
    process_add_instructions(&future_processes[2], CPU, 1);
    process_add_instructions(&future_processes[2], TAPE, 1);
    process_add_instructions(&future_processes[2], CPU, 4);  
}

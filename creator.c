/*
Este arquivo contém uma implementação para a API de creator.h.

Esta implementação gera um número predeterminado de processos, cujas instruções
também são predefinidas.

Esta implementação não é interativa.
*/
#include <stdio.h>
#include "process.h"
#include "scheduler.h"
#include "creator.h"
#include "output.h"

#define TOTAL_PROCESSES  3  // Total de processos predefinidos criados.

// Indica número de processos já criados.
// Usado como índice no array 'future_processes' do próximo processo a ser criado.
static uint8_t processes_created = 0;

// Array que contém os processos predefinidos que serão criados.
// Nesta declaração podemos indicar o tempo de início de cada processo.
// Para indicar as instruções dos processos, usar initialize_processes.
static Process future_processes[TOTAL_PROCESSES] = {
    {.start=0},
    {.start=5},
    {.start=5}
};

// -----

bool is_interactive = false;

extern int has_incoming_processes(){
    return processes_created < TOTAL_PROCESSES;
}

extern void create_processes(){    
    while (processes_created < TOTAL_PROCESSES){
        Process* p = &future_processes[processes_created];
        if (CPUtime == p->start){
            processes_created++;
            unsigned pid_gen = processes_created;
            
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

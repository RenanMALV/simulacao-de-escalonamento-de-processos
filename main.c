#include <stdio.h>
#include <stdint.h>

#include "process.h"
#include "queue.h"
#include "scheduler.h"
#include "devices.h"

// Tempo total de execução da CPU.
unsigned CPUtime = 0;

// Função usada para simular a chegada de novos processos.
void create_processes();

void initialize_processes();

void simulateCPU(){
    int instruction;
    while (currentProcess && (instruction = queue_pop(currentProcess->instructions)) != CPU){
        request_device(instruction);
    }
    
    if (currentProcess) printf("%d : %d\n", CPUtime, currentProcess->id);
    CPUtime++;
    timeUsed++;
}

//------------------------------------------------------------------------------
//                         S I M U L A D O R
//------------------------------------------------------------------------------
/*
 Para tornar mais fácil o entendimento do projeto, o simulador foi implementado
de forma modular.

 Cada fase do funcionamento da máquina é implementada por funções distintas. 
Para explorar a implementação dessas funções, basta navegar para o arquivo onde 
elas são definidas.
*/

int main(void){
    
    // Inicializar o sistema.
    devices_init();
    scheduler_init();
    initialize_processes();

    // Simular o loop de funcionamento do sistema:
    while (CPUtime < 100){
        // Passo 1: Simular a chegada de novos processos.
        create_processes(); // (implementação: ???.c (está implementado neste arquvio por enquanto))
        
        // Passo 2: Simular a execução do escalonador.
        scheduler();  // (implementação: scheduler.c)
        
        // Passo 3: Simular o processamento na CPU.
        simulateCPU();

        // Passo 4: Simular o processamento nos dispositivos de E/S.
        simulateIO(); // (implementação: devices.c)
    }
}

//------------------------------------------------------------------------------
// Process reation
#define TOTAL_PROCESSES  3
#define INITIAL_PRIORITY 0

uint8_t pid_gen = 0;
int future_index = 0;

Process future_processes[TOTAL_PROCESSES] = {
    {.start=0},
    {.start=5},
    {.start=5}
};


void create_processes(){
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
            printf("New process: %d\n", p->id);
            
            schedule_process(p);
        }
        else{
            return;
        }   
    }
}

void initialize_processes(){
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

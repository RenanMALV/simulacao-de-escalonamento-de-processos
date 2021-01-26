#include <stdio.h>
#include <stdint.h>

#include "process.h"
#include "queue.h"
#include "scheduler.h"
#include "devices.h"

#define TOTAL_PROCESSES  2

// Tempo total de execução da CPU.
unsigned CPUtime = 0;

// Função usada para simular a chegada de novos processos.
void create_processes();

// Simula o funcionamento dos dispositivos de E/S.
void simulateIO();

// Função que inicializa o sistema
void initialize();

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
    initialize();

    // Simular o loop de funcionamento do sistema:
    while (CPUtime < 100){
        // Passo 1: Simular a chegada de novos processos.
        create_processes(); // // (implementação: ???.c (está implementado neste arquvio por enquanto))
        
        // Passo 2: Simular a execução do escalonador.
        scheduler();  // (implementação: scheduler.c)
        
        // Passo 3: Simular o processamento na CPU.
        CPUtime++;

        // Passo 4: Simular o processamento nos dispositivos de E/S.
        simulateIO(); // (implementação: devices.c)
        
        // Mostrar tempo da CPU e o processo atual no console.
        if (currentProcess) printf("%d : %d\n", CPUtime, currentProcess->id);
    }
}

//------------------------------------------------------------------------------
// Process creation
uint8_t pid_gen = 0;
int future_index = 0;

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

void simulateIO(){
    for (int i = 0; i < IO_DEVICE_NUMBER; i++){
        int pid = simulate_device(i);
        
        if (pid){
            queue_push(ready_queues[IOdevices[i].priority], pid);
        }
    }
}

void initialize(){
    for (int i = 0; i < NUM_PRIORITIES; i++)
        ready_queues[i] = queue_create(NUM_PROCESSES);
        
    
    devices_init();
        
    future_processes[0].instructions = queue_create(20);
    process_add_instructions(&future_processes[0], CPU, 3);
    process_add_instructions(&future_processes[0], DISK, 1);
    process_add_instructions(&future_processes[0], CPU, 2);
    future_processes[1].instructions = queue_create(20);
    process_add_instructions(&future_processes[1], CPU, 5);

}

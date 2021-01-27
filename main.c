#include <stdio.h>
#include <stdint.h>

#include "process.h"
#include "queue.h"
#include "scheduler.h"
#include "devices.h"
#include "creator.h"

// Tempo total de execução da CPU.
unsigned CPUtime = 0;

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
    while (process_count > 0 || has_incoming_processes()){
        // Passo 1: Simular a chegada de novos processos.
        create_processes(); // (implementação: creator.c)
        
        // Passo 2: Simular a execução do escalonador.
        scheduler();  // (implementação: scheduler.c)
        
        // Passo 3: Simular o processamento na CPU.
        simulateCPU();

        // Passo 4: Simular o processamento nos dispositivos de E/S.
        simulateIO(); // (implementação: devices.c)
    }
}

//------------------------------------------------------------------------------

#pragma once

#include <stdint.h>
#include "process.h"
#include "queue.h"

// Número de filas de prioridade. Menor prioridade = mais prioritário.
#define NUM_PRIORITIES 2

// Quantum máximo para um processo no Round Robin.
#define MAX_TIME_USED 3


// Global que guarda um ponteiro para o processo a ser executado pela CPU.
extern Process* currentProcess;

// Global que guarda o tempo consumido pelo "currentProcess".
extern uint8_t timeUsed;

/*
 Esta é a função principal desse arquivo. Seu objetivo é simular a ação do escalondor,
e ela deve ser chamada antes da simulação da CPU (ou seja, antes do incremento de CPUtime).

 Ela irá setar o valor da global "currentProcess" para o próximo processo que será executado
pela CPU. Ela também é responsável por lidar com processos que pedem acesso a um dispositivo
de E/S.
*/
extern void scheduler();

// Bloqueia o currentProcess.
void scheduler_block();

// Coloca um processo na fila de processos prontos respectiva à sua prioridade.
void schedule_process(Process* p);

// Inicializa o escalonador. Deve ser chamada antes do laço principal do simulador.
void scheduler_init();

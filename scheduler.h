#pragma once

#include <stdint.h>
#include "process.h"
#include "queue.h"
#include "devices.h"

// Número de filas de prioridade. Menor prioridade = mais prioritário.
#define NUM_PRIORITIES 2

// Quantum máximo para um processo no Round Robin.
#define MAX_TIME_USED 3


// Global que guarda um ponteiro para o processo a ser executado pela CPU.
extern Process* currentProcess;

// Global que guarda o tempo consumido pelo "currentProcess".
extern uint8_t timeUsed;

// Inicializa o escalonador. Deve ser chamada antes do laço principal do simulador.
void scheduler_init();

// Bloqueia o currentProcess e atribui a essa variável o próximo processo.
void scheduler_block();

// Coloca um processo na fila de processos prontos referente à sua prioridade.
void schedule_process(Process* p);

/*
 Esta é a função principal desse arquivo. Seu objetivo é simular a ação do escalondor,
e ela deve ser chamada antes da simulação da CPU (ou seja, antes do incremento de CPUtime).

 Ela irá setar o valor da global "currentProcess" para o próximo processo que será executado
pela CPU. Ela também é responsável por lidar com processos que pedem acesso a um dispositivo
de E/S.
*/
void scheduler();

// -----
// As funções abaixo permitem explorar as filas de processos prontos.
// Elas não são utilizadas pelo simulador em si, são chamadas apenas para gerar a saída do programa no console.

// Tamanho da file de processos prontos para a dada prioridade.
unsigned scheduler_qlength(int priority);

// Wrapper de queue_foreach para a fila de processos prontos para a dada prioridade.
void scheduler_qforeach(int priority, void (*fun)(int));

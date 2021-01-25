#pragma once

#include <stdint.h>
#include "queue.h"

// Número máximo de processos que podem existir.
#define NUM_PROCESSES 20
#define IO_DEVICE_NUMBER 3

enum Instruction {DISK, TAPE, PRINTER, CPU};


typedef struct Process {
    unsigned start;
    Queue* instructions;
    
    unsigned id;  // Número de identificação do processo.
    unsigned IOcounter;
} Process;

// Tabela de processos (contém todos os processos vivos no sistema).
// Mapeia um id de processo para o ponteiro daquele processo.
extern Process* process_table[];

// Adiciona "amount" instruções do tipo "i" na fila do processo "p".
void process_add_instructions(Process* p, enum Instruction i, int amount);

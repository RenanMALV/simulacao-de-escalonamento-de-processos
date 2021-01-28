#pragma once

#define INITIAL_PRIORITY 0  // Prioridade atribuída a processos recém-criados.

extern unsigned CPUtime;

// Função usada para simular a chegada de novos processos.
void create_processes();

void initialize_processes();

int has_incoming_processes();

#pragma once

#include <stdbool.h>

#define INITIAL_PRIORITY 0  // Prioridade atribuída a processos recém-criados.

extern unsigned CPUtime;

// Determina se o programa vai rodar no modo interativo ou automático.
extern bool is_interactive;

// Função usada para simular a chegada de novos processos.
void create_processes();

void initialize_processes();

int has_incoming_processes();

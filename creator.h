#pragma once

extern unsigned CPUtime;

// Função usada para simular a chegada de novos processos.
void create_processes();

void initialize_processes();

int has_incoming_processes();

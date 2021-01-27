#pragma once

extern unsigned CPUtime;
// informa o estado atual das filas do sistema, além de identificar novos processos
extern void output_info(Process* p);

// Função usada para simular a chegada de novos processos.
void create_processes();

void initialize_processes();

int has_incoming_processes();

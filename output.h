/*
 As funções neste arquivo não estão relacionadas ao comportamento do simulador.
Elas apenas auxiliam na geração de saída no console.

 Sua implementação é realizada no arquivo main.c
*/
#pragma once

void output_event_preempt(Process* p);
void output_event_terminate(Process *p);
void output_event_iofinished(int device, Process* p);
void output_info(Process* p);

// informa o estado atual das filas do sistema, além de identificar novos processos
extern void output_info(Process* p);

#pragma once

#include "queue.h"

// Inicializa os dispositivos de E/S. Deve ser chamada antes do laço principal do simulador.
void devices_init();

// Pede uma operação de E/S em um certo dispositivo para o currentProcess.
// Bloqueia o processo automaticamente e altera sua prioridade.
void request_device(int deviceid);

// Retorna 0 se e somente não existe nenhum pedido de E/S incompleto no dispositivo.
int device_isactive(int deviceid);

/*
 Esta é a função principal deste arquivo. Seu objetivo é simular o funcionamento dos
dispositivos de E/S. Ela deve ser chamada após a simulação da CPU.

 Para cada dispositivo, ela irá simular a passagem de uma unidade de tempo. Se a
operação for completada, o processo será desbloqueado e colocada na respectiva fila
de prioridade pelo escalonador.
*/
void simulateIO();

// -----
// As funções abaixo permitem explorar as filas de processos esperando operações de E/S.
// Elas não são utilizadas pelo simulador em si, são chamadas apenas para gerar a saída do programa no console.

// Wrapper de queue_foreach para a fila de processos prontos para o IOdevice.
void device_qforeach(int deviceid, void (*fun)(TYPE));

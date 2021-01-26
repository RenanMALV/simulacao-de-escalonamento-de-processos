#pragma once

#include "process.h"

// Struct que representa um dispositivo de E/S e suas propriedades.
struct IODevice {
  const uint8_t duration;  // duração da operação de E/S para esse dispositivo.
  const uint8_t priority;  // prioridade com a qual um processo retorna à fila de prontos
  uint8_t counter;
};

// Array que guarda o respectivo IODevice para cada dispositivo (exemplo de uso: IOdevices[DISK].duration)
extern struct IODevice IOdevices[];

// Inicializa os dispositivos de E/S. Deve ser chamada antes do laço principal do simulador.
void devices_init();

// Pede uma operação de E/S em um certo dispositivo para um certo processo.
void request_device(int deviceid, int pid);

// Simula a operação de um dispositivo. Quando uma operação é completada, retorna o pid do processo. Senão retorna zero.
int simulate_device(int deviceid);

// Retorna 0 se e somente não existe nenhum pedido de E/S incompleto no dispositivo.
int device_isactive(int deviceid);

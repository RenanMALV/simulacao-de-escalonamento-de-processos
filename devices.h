#pragma once

#include "process.h"

// Struct que representa um dispositivo de E/S e suas propriedades.
struct IODevice {
  const uint8_t duration;  // duração da operação de E/S para esse dispositivo.
  const uint8_t priority;  // prioridade com a qual um processo retorna à fila de prontos.
};

// Array que guarda o respectivo IODevice para cada dispositivo (exemplo de uso: IOdevices[DISK].duration)
extern struct IODevice IOdevices[];

// Array que guarda as filas para cada dispositivo de E/S.
extern Queue* IOqueues[];

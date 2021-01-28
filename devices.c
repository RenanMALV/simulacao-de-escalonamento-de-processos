#include "devices.h"
#include "queue.h"
#include "scheduler.h"

// Struct que representa um dispositivo de E/S e suas propriedades.
struct IODevice {
  const uint8_t duration;  // duração da operação de E/S para esse dispositivo.
  const uint8_t priority;  // prioridade com a qual um processo retorna à fila de prontos
  uint8_t counter;
  Queue* queue;            // fila de processos que pediram uma operação no dispositivo.
};

// Array que guarda as structs que representam cada dispositivo.
static struct IODevice IOdevices[IO_DEVICE_NUMBER] = {
    {.duration=4,  .priority=1 },  // Disk
    {.duration=7,  .priority=0 },  // Tape
    {.duration=20, .priority=0 }   // Printer
};

// Simula a operação de um dispositivo. Quando uma operação é completada, retorna o pid do processo. Senão retorna zero.
static int simulate_device(int i){
    struct IODevice* device = &IOdevices[i];
    // Verifica se existe algum processo solicitando operação no dispositivo
    if (device_isactive(i)){
        if (--(device->counter) == 0){
            device->counter = device->duration;
            return queue_pop(IOdevices[i].queue);
        }
    }
    
    return 0;
}

// -----

extern int device_isactive(int deviceid){
    return !queue_isempty(IOdevices[deviceid].queue);
}

extern void request_device(int deviceid){
    struct IODevice* device = &IOdevices[deviceid];
    
    queue_push(device->queue, currentProcess->id);
    
    currentProcess->priority = device->priority;
    scheduler_block();
}

extern void simulateIO(){
    for (int i = 0; i < IO_DEVICE_NUMBER; i++){
        // Se o tempo de operação no dispositivo terminou, retorna o ID do processo que solicitou a operação, se não, retorna 0.
        int pid = simulate_device(i);
        
        if (pid){
            schedule_process(process_table[pid]);
        }
    }
}

extern void devices_init(){
    for (int i = 0; i < IO_DEVICE_NUMBER; i++){
        IOdevices[i].queue = queue_create(NUM_PROCESSES);
        IOdevices[i].counter = IOdevices[i].duration;
    }
}

extern void device_qforeach(int deviceid, void (*fun)(TYPE)){
    queue_foreach(IOdevices[deviceid].queue, fun);
}

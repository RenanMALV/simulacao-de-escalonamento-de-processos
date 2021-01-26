#include "devices.h"
#include "queue.h"

// Array que guarda as filas de processos para cada dispositivo de E/S.
static Queue* IOqueues[IO_DEVICE_NUMBER];

struct IODevice IOdevices[IO_DEVICE_NUMBER] = {
    {.duration=4,  .priority=1 },  // Disk
    {.duration=7,  .priority=0 },  // Tape
    {.duration=20, .priority=0 }   // Printer
};

int device_isactive(int deviceid){
    return !queue_isempty(IOqueues[deviceid]);
}

void request_device(int deviceid, int pid){
    queue_push(IOqueues[deviceid], pid);
}


int simulate_device(int i){
    struct IODevice* device = &IOdevices[i];
    
    if (device_isactive(i)){
        if (--(device->counter) == 0){
            device->counter = device->duration;
            return queue_pop(IOqueues[i]);
        }
    }
    
    return 0;
}

void devices_init(){
    for (int i = 0; i < IO_DEVICE_NUMBER; i++){
        IOqueues[i] = queue_create(NUM_PROCESSES);
        IOdevices[i].counter = IOdevices[i].duration;
    }
        
}

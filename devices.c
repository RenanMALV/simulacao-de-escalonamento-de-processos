#include "devices.h"

Queue* IOqueues[IO_DEVICE_NUMBER];

struct IODevice IOdevices[IO_DEVICE_NUMBER] = {
    {.duration=4,  .priority=1},  // Disk
    {.duration=7,  .priority=0},  // Tape
    {.duration=20, .priority=0}   // Printer
};

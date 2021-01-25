#pragma once

#include "process.h"
#include "queue.h"

#define NUM_PRIORITIES 2
#define MAX_TIME_USED 3

extern Process* currentProcess;
extern Queue* ready_queues[];

extern uint8_t timeUsed;

extern Queue* IOqueues[];

extern void scheduler();

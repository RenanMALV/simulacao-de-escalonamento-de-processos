#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#include "process.h"
#include "scheduler.h"
#include "creator.h"
#include "output.h"

// Set to a negative number for infinite simulation.
#define MAX_CPU_TIME 100
#define NUM_SIMULTANEOUS 20// NUM_PROCESSES

static Queue* unused_ids;

Process processes[NUM_SIMULTANEOUS+1];


#define randrange(start,end) int randrange_i=(start),randrange_end=(start)+rand()%(end); randrange_i <= randrange_end; randrange_i++

static void randomize_process(Process* p){
    static const enum Instruction instrs[6] = {DISK, DISK, TAPE, PRINTER, CPU, CPU};
    static const uint8_t          amount[6]  = {1   , 2   , 1   , 1      , 2  , 3  };
    
    for(randrange(1,3)){
        process_add_instructions(p, CPU, 2 + rand()%4);
        const int r = rand()%6;
        process_add_instructions(p, instrs[r], amount[r]);
    }
    
     // Última instrução deve ser CPU.
    if(p->instructions->array[p->instructions->last] != CPU){
        if (queue_isfull(p->instructions))
            p->instructions->array[p->instructions->last] = CPU; 
        else
            queue_push(p->instructions, CPU);
    }
}

// -----

bool is_interactive = true;

extern int has_incoming_processes(){
    #if (MAX_CPU_TIME >= 0)
        return CPUtime <= MAX_CPU_TIME;
    #else
        return 1;
    #endif
}

extern void create_processes(){
    for(randrange(0,2)){
        if (unused_ids->length){
            const int pid = queue_pop(unused_ids);
            processes[pid] = (Process) {.start=CPUtime, .priority=INITIAL_PRIORITY, .id = pid, .state=PSTATE_CREATED, .instructions=queue_create(20)};
            randomize_process(&processes[pid]);
            output_info(&processes[pid]);
            process_table[pid] = &processes[pid];
            process_count++;
            
            schedule_process(&processes[pid]);
        }
        else if (process_count < NUM_PROCESSES){
            for (int i = 0; i < NUM_PROCESSES; i++)
                if (processes[i].state == PSTATE_TERMINATED)
                    queue_push(unused_ids, i);
        }
    }
}

extern void initialize_processes(){
    srand(time(NULL));
    unused_ids = queue_create(NUM_SIMULTANEOUS);
    for (int i = 1; i <= NUM_SIMULTANEOUS; i++){
        queue_push(unused_ids, i);
    }
}

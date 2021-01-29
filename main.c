#include <stdio.h>
#include <stdint.h>

//função sleep
#include <unistd.h>

#include "process.h"
#include "queue.h"
#include "scheduler.h"
#include "devices.h"
#include "creator.h"
#include "output.h"

// Tempo total de execução da CPU.
unsigned CPUtime = 0;

const char* device_names[3] = {"DISK", "TAPE", "PRINTER"};

void get_user_input();

void simulateCPU(){
    int instruction;
    while(currentProcess && (instruction = queue_pop(currentProcess->instructions)) != CPU){
        printf("[Tick %d]\tCPU: REQUEST %s (pid %d)\n", CPUtime, device_names[instruction], currentProcess->id);
        request_device(instruction);
    }
    
    timeUsed++;
    output_info(currentProcess);
    
    // sleep(1);
    
    CPUtime++;
    
}

//------------------------------------------------------------------------------
//                         S I M U L A D O R
//------------------------------------------------------------------------------
/*
 Para tornar mais fácil o entendimento do projeto, o simulador foi implementado
de forma modular.

 Cada fase do funcionamento da máquina é implementada por funções distintas. 
Para explorar a implementação dessas funções, basta navegar para o arquivo onde 
elas são definidas.
*/

int main(void){
    
    // Inicializar o sistema.
    devices_init();
    scheduler_init();
    initialize_processes();

    // Simular o loop de funcionamento do sistema:
    while (process_count > 0 || has_incoming_processes()){
        // Passo 1: Simular a chegada de novos processos.
        create_processes(); // (implementação: creator.c)
        
        // Passo 2: Simular a execução do escalonador.
        scheduler();  // (implementação: scheduler.c)
        
        // Passo 3: Simular o processamento na CPU.
        simulateCPU();

        // Passo 4: Simular o processamento nos dispositivos de E/S.
        simulateIO(); // (implementação: devices.c)
        
        if (is_interactive) get_user_input();
    }
}

//------------------------------------------------------------------------------
// Código usado para gerar a saída do programar e mostar informações da simulação.

static const char instruction_chars[4] = {'D', 'T', 'P', 'C'};
static const char* priority_names[2] = {"HIGH", "LOW"};

#define SHOW_EMPTY_QUEUES 1
#define SHOW_EVENTS 1

void get_user_input(){
    printf("Press enter to continue...");
    while (getchar() != '\n'){};
}

static void print_int(TYPE pid){
    printf("%d ", pid);
}

static void print_instruction(TYPE i){
    printf("%c", instruction_chars[i]);
}

static void print_queues(){
    for (int i =0; i < NUM_PRIORITIES; i++){
        if (SHOW_EMPTY_QUEUES || scheduler_qlength(i) > 0){
           printf("[Tick %d]\tReady Queue (%s): { ", CPUtime, priority_names[i]);
            scheduler_qforeach(i, *print_int);
            printf("}\n"); 
        }
    }
    
    for (int i =0; i < IO_DEVICE_NUMBER; i++){
        if (SHOW_EMPTY_QUEUES || device_isactive(i)){
           printf("[Tick %d]\tI/O Queue (%s): { ", CPUtime, device_names[i]);
            device_qforeach(i, *print_int);
            printf("}\n"); 
        }
    }
    
    
    printf("\n");
}

// -----

extern void output_event_preempt(Process* p){
    if (SHOW_EVENTS)
        printf("[Tick %d]\tSCHEDULER: PREEMPT (pid %d)\n", CPUtime, p->id);
}

extern void output_event_terminate(Process *p){
    if (SHOW_EVENTS)
        printf("[Tick %d]\tSCHEDULER: TERMINATE (pid %d)\n", CPUtime, p->id);
}

extern void output_event_iofinished(int device, Process* p){
    if (SHOW_EVENTS)
        printf("[Tick %d]\t%s: FINISHED (pid %d)\n", CPUtime, device_names[device], p->id);
}

extern void output_info(Process* p){
    printf("[Tick %d]\t", CPUtime);

    if (p){
        if (p->state == PSTATE_CREATED){
            printf("New process: pid %d (", p->id);
            queue_foreach(p->instructions, &print_instruction);
            printf(")\n");
        }
        else{
            printf("CPU: RUNNING (pid %d) - t=%d\n", p->id, timeUsed);
            print_queues();
        }
            
    }
    else{
        printf("CPU: IDLE - t=%d\n", timeUsed);
        print_queues();
    }
        

}

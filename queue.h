/*
    Arquivo contendo a API que será utilizada para filas no projeto.
*/

#pragma once

#include <stdlib.h>

 // Defina aqui o tipo dos elementos guardados na fila.
 typedef short TYPE;

typedef struct Queue { 
    TYPE* array;
    int first, last;  // apontam posições no array da fila
    unsigned length, maxlength; 
} Queue;

// Cria uma fila com uma certa capacidade.
Queue* queue_create(unsigned maxlength);

// Copia uma fila, retornando uma nova fila idêntica.
Queue* queue_copy(Queue* original);

// Fila está cheia?
int queue_isfull(Queue* queue);

// Fila está vazia?
int queue_isempty(Queue* queue);

// Retorna o primeiro elemento da fila.
TYPE queue_peek(Queue* queue);

// Retorna o n-ésimo elemento da fila.
TYPE queue_peekn(Queue* queue, unsigned n);

// Coloca um elemento no final da fila.
void queue_push(Queue* queue, TYPE item);

// Tira o elemento do início da fila e o retorna.
TYPE queue_pop(Queue* queue);

// Executa uma função para cada valor na fila.
void queue_foreach(Queue* queue, void (*fun)(TYPE));

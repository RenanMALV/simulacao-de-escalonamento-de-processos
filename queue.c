/*
    Arquivo contendo a implementação de uma fila utilizando um array acessado de forma circular.
*/
#include "queue.h"


Queue* queue_create(unsigned maxlength) { 
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    
    queue->first = queue->length = 0;
    queue->last = maxlength - 1;  // inicializando assim, se tornará 0 na primeira chamada de "push".
    queue->maxlength = maxlength;
    
    queue->array = (TYPE*) malloc(maxlength * sizeof(TYPE));
    return queue;
} 

Queue* queue_copy(Queue* original) { 
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    
    queue->first = original->first;
    queue->length = original->length;
    queue->last = original->last;
    queue->maxlength = original->maxlength;
    
    queue->array = (TYPE*) malloc(queue->maxlength * sizeof(TYPE));
    
    
    if (queue->length > 0){
        if (queue->first > queue->last){
            for (int i=queue->first; i < queue->maxlength; i++)
                    queue->array[i] = original->array[i];
                    
            for (int i=0; i <= queue->last; i++)
                    queue->array[i] = original->array[i];
        } else{
            for (int i=queue->first; i <= queue->last; i++)
                    queue->array[i] = original->array[i];
        }
    }
    
    return queue;
}

int queue_isfull(Queue* queue) {
    return (queue->length == queue->maxlength);
}

int queue_isempty(Queue* queue) {
    return !(queue->length);
}

TYPE queue_peek(Queue* queue) {
    return queue->array[queue->first];
}

TYPE queue_peekn(Queue* queue, unsigned n) {
    return queue->array[(n + queue->first) % queue->maxlength];
}

void queue_push(Queue* queue, TYPE item) {
    if (!queue_isfull(queue)) {
        queue->last = (queue->last + 1) % queue->maxlength;
        queue->array[queue->last] = item;
        queue->length++;
    }
}

// Tira o elemento do início da fila e o retorna.
TYPE queue_pop(Queue* queue) {
    TYPE item = queue_peek(queue);
    queue->first = (queue->first + 1) % queue->maxlength;
    queue->length--; 
    return item;
}

void queue_foreach(Queue* queue, void (*fun)(TYPE)) {
    if (queue->length > 0){
        if (queue->first > queue->last){
            for (int i=queue->first; i < queue->maxlength; i++)
                    (*fun)(queue->array[i]);
                    
            for (int i=0; i <= queue->last; i++)
                    (*fun)(queue->array[i]);
        } else{
            for (int i=queue->first; i <= queue->last; i++)
                    (*fun)(queue->array[i]);
        }
    }
}

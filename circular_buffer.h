#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFF_SIZE 100

typedef struct Circular_buffer
{
    unsigned int head_index, tail_index;
    size_t current_number_of_elements;
    double buffer[BUFF_SIZE];
    pthread_mutex_t mutex_circular_buffer;
    pthread_cond_t cond_buffer_is_empty;
    pthread_cond_t cond_buffer_is_full;
} Circular_buffer;

Circular_buffer* circular_buffer_init(void);
void circular_buffer_push(Circular_buffer* circular_buffer, const double processor_data);
double circular_buffer_pop(Circular_buffer* circular_buffer);
void circular_buffer_destroy(Circular_buffer* circular_buffer);

#endif // CIRCULAR_BUFFER_H

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

extern FILE* logger_file;

typedef struct Circular_buffer
{
    unsigned int head_index, tail_index;
    size_t current_number_of_elements, capacity;
    pthread_mutex_t mutex_circular_buffer;
    pthread_cond_t cond_buffer_is_empty;
    pthread_cond_t cond_buffer_is_full;
    double buffer[];
} Circular_buffer;

Circular_buffer* circular_buffer_init(const size_t buffer_size);
void circular_buffer_push(Circular_buffer* circular_buffer, const double processor_data);
double circular_buffer_pop(Circular_buffer* circular_buffer);
void circular_buffer_destroy(Circular_buffer* circular_buffer);

#endif // CIRCULAR_BUFFER_H

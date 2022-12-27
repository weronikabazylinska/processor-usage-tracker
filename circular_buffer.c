#include "circular_buffer.h"

Circular_buffer* circular_buffer_init(const size_t buffer_size)
{
    Circular_buffer* circular_buffer = malloc(sizeof(Circular_buffer) + sizeof(double) * buffer_size);
    if(circular_buffer == NULL)
    {
        char* error = "ERROR: Failed to allocate memory for circular buffer\n";
        perror(error);
        fprintf(logger_file, "%s", error);
        return circular_buffer;
    }

    circular_buffer->head_index = 0;
    circular_buffer->tail_index = 0;
    circular_buffer->current_number_of_elements = 0;
    circular_buffer->capacity = buffer_size;

    pthread_mutex_init(&circular_buffer->mutex_circular_buffer, NULL);
    pthread_cond_init(&circular_buffer->cond_buffer_is_empty, NULL);
    pthread_cond_init(&circular_buffer->cond_buffer_is_full, NULL);

    return circular_buffer;
}

bool is_circular_buffer_full(const Circular_buffer* circular_buffer)
{
    if(circular_buffer == NULL)
    {
        char* error = "ERROR: Pointer to circular buffer is NULL\n";
        perror(error);
        fprintf(logger_file, "%s", error);
        return 1;
    }
    if(circular_buffer->current_number_of_elements == circular_buffer->capacity)
    {
        return true;
    }
    return false;
}

void circular_buffer_push(Circular_buffer* circular_buffer, const double processor_data)
{
    if(circular_buffer == NULL)
    {
        char* error = "ERROR: Pointer to circular buffer is NULL\n";
        perror(error);
        fprintf(logger_file, "%s", error);
        return;
    }

    pthread_mutex_lock(&circular_buffer->mutex_circular_buffer);
    while(is_circular_buffer_full(circular_buffer))
    {
        pthread_cond_wait(&circular_buffer->cond_buffer_is_full, &circular_buffer->mutex_circular_buffer);
    }

    circular_buffer->buffer[circular_buffer->tail_index] = processor_data;
    circular_buffer->tail_index = (circular_buffer->tail_index + 1) % circular_buffer->capacity;
    ++circular_buffer->current_number_of_elements;
    pthread_mutex_unlock(&circular_buffer->mutex_circular_buffer);
}

bool is_circular_buffer_empty(const Circular_buffer* circular_buffer)
{
     if(circular_buffer == NULL)
    {
        char* error = "ERROR: Pointer to circular buffer is NULL\n";
        perror(error);
        fprintf(logger_file, "%s", error);
        return 1;
    }
    if(circular_buffer->current_number_of_elements == 0)
    {
        return true;
    }
    return false;
}

double circular_buffer_pop(Circular_buffer* circular_buffer)
{
    if(circular_buffer == NULL)
    {
        char* error = "ERROR: Pointer to circular buffer is NULL\n";
        perror(error);
        fprintf(logger_file, "%s", error);
        return 1;
    }

    pthread_mutex_lock(&circular_buffer->mutex_circular_buffer);
    while(is_circular_buffer_empty(circular_buffer))
    {
        pthread_cond_wait(&circular_buffer->cond_buffer_is_empty, &circular_buffer->mutex_circular_buffer);
    }

    double processor_data = circular_buffer->buffer[circular_buffer->head_index];
    circular_buffer->head_index = (circular_buffer->head_index + 1) % circular_buffer->capacity;
    --circular_buffer->current_number_of_elements;
    pthread_mutex_unlock(&circular_buffer->mutex_circular_buffer);

    return processor_data;
}

void circular_buffer_destroy(Circular_buffer* circular_buffer)
{
    if(circular_buffer == NULL)
    {
        return;
    }

    pthread_mutex_destroy(&circular_buffer->mutex_circular_buffer);
    pthread_cond_destroy(&circular_buffer->cond_buffer_is_empty);
    pthread_cond_destroy(&circular_buffer->cond_buffer_is_full);

    free(circular_buffer);
    circular_buffer = NULL;
}

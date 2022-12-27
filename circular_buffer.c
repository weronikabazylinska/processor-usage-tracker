#include "circular_buffer.h"

Circular_buffer* circular_buffer_init(void)
{
    Circular_buffer* circular_buffer = malloc(sizeof(Circular_buffer));
    if(circular_buffer == NULL)
    {
        char* error = "ERROR: Failed to allocate memory for circular buffer\n";
        return circular_buffer;
    }

    circular_buffer->head_index = 0;
    circular_buffer->tail_index = 0;
    circular_buffer->current_number_of_elements = 0;

    return circular_buffer;
}

void circular_buffer_push(Circular_buffer* circular_buffer, const double processor_data)
{
    if(circular_buffer->current_number_of_elements == (BUFF_SIZE - 1))
    {
        perror("ERROR: circular buffer push failed, buffer is full\n");
        return;
    }
    circular_buffer->buffer[circular_buffer->tail_index] = processor_data;
    circular_buffer->tail_index = (circular_buffer->tail_index + 1) % BUFF_SIZE;
    ++circular_buffer->current_number_of_elements;
}

double circular_buffer_pop(Circular_buffer* circular_buffer)
{
    if(circular_buffer->current_number_of_elements == 0)
    {
        perror("ERROR: circular buffer pop failed, buffer is empty\n");
        return -1;
    }
    double processor_data = circular_buffer->buffer[circular_buffer->head_index];
    circular_buffer->head_index = (circular_buffer->head_index + 1) % BUFF_SIZE;
    --circular_buffer->current_number_of_elements;

    return processor_data;
}

void circular_buffer_destroy(Circular_buffer* circular_buffer)
{
    if(circular_buffer == NULL)
    {
        return;
    }

    free(circular_buffer);
    circular_buffer = NULL;
}

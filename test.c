#include "test.h"

#define DATA_SIZE 10

void test_circular_buffer_init(void)
{
    assert(circular_buffer_init() != NULL);
}

void test_circular_buffer_push_and_pop(void)
{
    Circular_buffer* circular_buffer = circular_buffer_init();

    double source_data[DATA_SIZE] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};

    for(size_t i = 0; i < DATA_SIZE; ++i)
    {
        circular_buffer_push(circular_buffer, source_data[i]);
    }

    double acquired_data[DATA_SIZE];
    for(size_t i = 0; i < DATA_SIZE; ++i)
    {
        acquired_data[i] = circular_buffer_pop(circular_buffer);
    }

    assert(memcmp(source_data, acquired_data, DATA_SIZE) == 0);
}

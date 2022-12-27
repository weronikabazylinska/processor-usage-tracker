#include "circular_buffer.h"
#include "reader.h"
#include <pthread.h>

int main(void)
{
    test_circular_buffer_init();
    test_circular_buffer_push_and_pop();

    Circular_buffer* circular_buffer_processor_data = circular_buffer_init();
    read_proc_stat(circular_buffer_processor_data);

    pthread_t reader;
    if(pthread_create(&reader, NULL, reader_thread, &circular_buffer_processor_data) != 0)
    {
         perror("Failed to create reader thread\n");
         return 1;
    }

    pthread_join(reader, NULL);

    circular_buffer_destroy(circular_buffer_processor_data);
    return 0;
}

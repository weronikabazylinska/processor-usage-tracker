#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include <pthread.h>

typedef enum Threads
{
    reader = 0,
    analyzer,
    printer,
    number_of_threads
}Threads;

int main(void)
{
    test_circular_buffer_init();
    test_circular_buffer_push_and_pop();

    Circular_buffer* circular_buffer_processor_data = circular_buffer_init();
    Circular_buffer* circular_buffer_processor_usage = circular_buffer_init();

    read_proc_stat(circular_buffer_processor_data);

    Thread_data thread_data;
    thread_data.cpu_data.circular_buffer = circular_buffer_processor_data;
    thread_data.cpu_data.are_sem_init = false;
    thread_data.cpu_usage.circular_buffer = circular_buffer_processor_usage;

    pthread_t th[number_of_threads];
    if(pthread_create(&th[reader], NULL, reader_thread, &thread_data) != 0)
    {
         perror("Failed to create reader thread\n");
         return 1;
    }
    if(pthread_create(&th[analyzer], NULL, analyzer_thread, &thread_data) != 0)
    {
         perror("Failed to create analyzer thread\n");
         return 2;
    }
    if(pthread_create(&th[printer], NULL, printer_thread, &thread_data) != 0)
    {
         perror("Failed to create printer thread\n");
         return 3;
    }

    for(size_t i = reader; i < number_of_threads; ++i)
    {
        pthread_join(th[i], NULL);
    }

    circular_buffer_destroy(circular_buffer_processor_data);
    circular_buffer_destroy(circular_buffer_processor_usage);
    return 0;
}

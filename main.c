#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "logger.h"
#include <string.h>

extern FILE* logger_file;

typedef enum Threads
{
    reader = 0,
    analyzer,
    printer,
    logger,
    number_threads
}Threads;

int main(void)
{
    Circular_buffer* circular_buffer_processor_data = circular_buffer_init();
    Circular_buffer* circular_buffer_processor_usage = circular_buffer_init();

    read_proc_stat(circular_buffer_processor_data);

    Thread_data thread_data;
    thread_data.cpu_data.circular_buffer = circular_buffer_processor_data;
    thread_data.cpu_data.are_sem_init = false;
    thread_data.cpu_usage.circular_buffer = circular_buffer_processor_usage;
    thread_data.cpu_usage.are_sem_init = false;
    thread_data.data_logger.is_sem_init = false;

    pthread_t th[number_threads];
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
    if(pthread_create(&th[logger], NULL, logger_thread, &thread_data) != 0)
    {
         perror("Failed to create logger thread\n");
         return 4;
    }

    for(size_t i = reader; i < number_threads; ++i)
    {
        pthread_join(th[i], NULL);
    }

    circular_buffer_destroy(circular_buffer_processor_data);
    circular_buffer_destroy(circular_buffer_processor_usage);

    return 0;
}

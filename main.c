#include "reader.h"
#include "analyzer.h"
#include "printer.h"
#include "logger.h"
#include "watchdog.h"
#include <string.h>

extern FILE* logger_file;

typedef enum Threads
{
    reader = 0,
    analyzer,
    printer,
    logger,
    watchdog,
    number_threads
}Threads;

volatile sig_atomic_t done = 0;
static void term(int signum)
{
    if(signum == 15)
    {
        done = 1;
        fprintf(logger_file, "%s", "SINGTERM caught\n");
    }
}

int main(void)
{
    Circular_buffer* circular_buffer_processor_data = circular_buffer_init();
    Circular_buffer* circular_buffer_processor_usage = circular_buffer_init();

    read_proc_stat(circular_buffer_processor_data);

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

    Thread_data thread_data;
    thread_data.cpu_data.circular_buffer = circular_buffer_processor_data;
    thread_data.cpu_data.are_sem_init = false;
    thread_data.cpu_usage.circular_buffer = circular_buffer_processor_usage;
    thread_data.cpu_usage.are_sem_init = false;
    thread_data.data_logger.is_sem_init = false;
    thread_data.flag_watchdog = reset_flag;

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
    if(pthread_create(&th[watchdog], NULL, watchdog_thread, &thread_data) != 0)
    {
         perror("Failed to create logger thread\n");
         return 5;
    }

    for(size_t i = reader; i < number_threads; ++i)
    {
        pthread_join(th[i], NULL);
    }

    circular_buffer_destroy(circular_buffer_processor_data);
    circular_buffer_destroy(circular_buffer_processor_usage);

    return 0;
}

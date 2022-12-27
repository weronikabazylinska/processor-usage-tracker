#include "logger.h"

FILE* logger_file;

void* logger_thread(void* thread_data)
{
    Thread_data* t_data = (Thread_data*)thread_data;
    while(t_data->data_logger.is_sem_init == false)
    {
        sleep(1);
    }

    logger_file = fopen("log.txt", "a");
    if(logger_file == NULL)
    {
        char* error = "Failed to open file /proc/stat\n";
        perror(error);
        fprintf(logger_file, "%s", error);

        return thread_data;
    }

    unsigned int seconds_counter = 1;
    fprintf(logger_file,"second\t CPU usage\n");

    while((t_data->flag_watchdog != exec_stop)&& (!done))
    {
        sem_wait(&t_data->data_logger.sem);
        fprintf(logger_file,"%6u\t %8.2f%%\n", seconds_counter++, t_data->data_logger.processor_usage);

        if(t_data->flag_watchdog != exec_stop)
        {
            t_data->flag_watchdog |= exec_logger;
        }
    }

    if(t_data->data_logger.is_sem_init == true)
    {
        sem_destroy(&t_data->data_logger.sem);
        t_data->data_logger.is_sem_init = false;
    }

    fclose(logger_file);

    return thread_data;
}

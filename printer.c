#include "printer.h"

void* printer_thread(void* thread_data)
{
    Thread_data* t_data =(Thread_data*)thread_data;

    while(t_data->cpu_usage.are_sem_init == false)
    {
        sleep(1);
    }

    while(1)
    {
        sem_wait(&t_data->cpu_usage.sem_full);
        double processor_usage = circular_buffer_pop(t_data->cpu_usage.circular_buffer);
        pthread_cond_signal(&t_data->cpu_usage.circular_buffer->cond_buffer_is_full);
        system("clear");
        printf("CPU usage: %.2lf\n", processor_usage);
        sem_post(&t_data->cpu_usage.sem_empty);
    }

    if(t_data->cpu_usage.are_sem_init == true)
    {
        sem_destroy(&t_data->cpu_usage.sem_empty);
        sem_destroy(&t_data->cpu_usage.sem_full);
        t_data->cpu_usage.are_sem_init = false;
    }

    return thread_data;
}

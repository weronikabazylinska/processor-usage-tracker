#include "analyzer.h"

void* analyzer_thread(void* thread_data)
{
    Thread_data* t_data = (Thread_data*)thread_data;
    if(t_data->cpu_usage.are_sem_init == false)
    {
        sem_init(&t_data->cpu_usage.sem_empty, 0, BUFF_SIZE);
        sem_init(&t_data->cpu_usage.sem_full, 0, 0);
        t_data->cpu_usage.are_sem_init = true;
    }

    while(t_data->cpu_data.are_sem_init == false)
    {
        sleep(1);
    }

    Components_processed_data previous = calculate_components_proccesed_data(t_data->cpu_data.circular_buffer);
    Components_processed_data current;

    while((t_data->flag_watchdog != exec_stop) && (!done))
    {
        sem_wait(&t_data->cpu_data.sem_full);
        current = calculate_components_proccesed_data(t_data->cpu_data.circular_buffer);
        pthread_cond_signal(&t_data->cpu_data.circular_buffer->cond_buffer_is_full);
        sem_post(&t_data->cpu_data.sem_empty);

        sem_wait(&t_data->cpu_usage.sem_empty);
        double processed_data = calculate_proccesed_data(&previous, &current);
        circular_buffer_push(t_data->cpu_usage.circular_buffer, processed_data);
        pthread_cond_signal(&t_data->cpu_usage.circular_buffer->cond_buffer_is_empty);
        sem_post(&t_data->cpu_usage.sem_full);

        if(t_data->flag_watchdog != exec_stop)
        {
            t_data->flag_watchdog |= exec_analyzer;
        }
    }

    if(t_data->cpu_data.are_sem_init == true)
    {
        sem_destroy(&t_data->cpu_data.sem_empty);
        sem_destroy(&t_data->cpu_data.sem_full);
        t_data->cpu_data.are_sem_init = false;
    }

    return thread_data;
}

Components_processed_data calculate_components_proccesed_data(Circular_buffer* circular_buffer)
{
    double data_processor_mode[number_of_proccesor_modes];
    for(size_t i = idle_mode; i < number_of_proccesor_modes; ++i)
    {
        data_processor_mode[i] = circular_buffer_pop(circular_buffer);
    }

    double idle = data_processor_mode[idle_mode] + data_processor_mode[iowait_mode];
    double nonIdle = data_processor_mode[user_mode] + data_processor_mode[nice_mode]
                   + data_processor_mode[system_mode] + data_processor_mode[irq_mode]
                   + data_processor_mode[softirq_mode] + data_processor_mode[steal_mode];
    double total = idle + nonIdle;

    Components_processed_data components_processed_data;
    components_processed_data.idle_processed_data = idle;
    components_processed_data.total_proccesed_data = total;

    return components_processed_data;
}

double calculate_proccesed_data(Components_processed_data* previous, Components_processed_data* current)
{
    double idle = current->idle_processed_data - previous->idle_processed_data;
    double total = current->total_proccesed_data - previous->total_proccesed_data;

    double proccesed_data = ((total - idle) / total) * 100;

    return proccesed_data;
}

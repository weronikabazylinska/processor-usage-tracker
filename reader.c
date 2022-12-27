#include "reader.h"

void* reader_thread(void* thread_data)
{
    Thread_data* t_data = (Thread_data*)thread_data;
    if(t_data->cpu_data.are_sem_init == false)
    {
        sem_init(&t_data->cpu_data.sem_empty, 0, BUFF_SIZE);
        sem_init(&t_data->cpu_data.sem_full, 0, 0);
        t_data->cpu_data.are_sem_init= true;
    }

    while(1)
    {
        sem_wait(&t_data->cpu_data.sem_empty);
        sleep(1);
        read_proc_stat(t_data->cpu_data.circular_buffer);
        pthread_cond_signal(&t_data->cpu_data.circular_buffer->cond_buffer_is_empty);
        sem_post(&t_data->cpu_data.sem_full);
    }

    return thread_data;
}

void read_proc_stat(Circular_buffer* circular_buffer)
{
    FILE* proc_stat_file = fopen("/proc/stat", "r");
    if(proc_stat_file == NULL)
    {
        perror("ERROR: Failed to open file /proc/stat\n");
        return;
    }

    char string[4];
    if(fscanf(proc_stat_file, "%s", string) != 1)
    {
        perror("ERROR: fscanf() failed\n");
        return;
    }

    double data_processor_modes[number_of_proccesor_modes];

    int result = fscanf(proc_stat_file, "%lf %lf %lf %lf %lf %lf %lf %lf ",
                           &data_processor_modes[user_mode],
                           &data_processor_modes[nice_mode],
                           &data_processor_modes[system_mode],
                           &data_processor_modes[idle_mode],
                           &data_processor_modes[iowait_mode],
                           &data_processor_modes[irq_mode],
                           &data_processor_modes[softirq_mode],
                           &data_processor_modes[steal_mode]);

    if(result != number_of_proccesor_modes)
    {
        perror("ERROR: fscanf() failed\n");
        return;
    }

    for(size_t i = 0; i < number_of_proccesor_modes; ++i)
    {
        circular_buffer_push(circular_buffer, data_processor_modes[i]);
    }

    fclose(proc_stat_file);
}

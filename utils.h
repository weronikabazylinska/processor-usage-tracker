#ifndef UTILS_H
#define UTILS_H

#include "circular_buffer.h"
#include <stdbool.h>
#include <semaphore.h>

extern FILE* logger_file;

typedef struct Data
{
    Circular_buffer* circular_buffer;
    bool are_sem_init;
    sem_t sem_empty, sem_full;
} Data;

typedef struct Data_logger
{
    double processor_usage;
    bool is_sem_init;
    sem_t sem;
} Data_logger;

typedef struct Thread_data
{
   Data cpu_data;
   Data cpu_usage;
   Data_logger data_logger;
} Thread_data;

typedef enum Processor_mode
{
    idle_mode = 0, iowait_mode, //idle
    user_mode, nice_mode, system_mode, irq_mode, softirq_mode, steal_mode,//non idle
    number_of_proccesor_modes
} Processor_mode;

#endif // UTILS_H

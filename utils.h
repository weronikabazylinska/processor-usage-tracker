#ifndef UTILS_H
#define UTILS_H

#include "circular_buffer.h"
#include <semaphore.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <signal.h>

extern FILE* logger_file;
extern volatile sig_atomic_t done;

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
   atomic_uint flag_watchdog;
} Thread_data;

typedef enum Processor_mode
{
    idle_mode = 0, iowait_mode, //idle
    user_mode, nice_mode, system_mode, irq_mode, softirq_mode, steal_mode,//non idle
    number_of_proccesor_modes
} Processor_mode;

typedef enum Flag_settings
{
    reset_flag = 0,
    exec_reader = 1 << 0,
    exec_analyzer = 1 << 1,
    exec_printer = 1 << 2,
    exec_logger = 1 << 3,
    exec_all = exec_reader | exec_analyzer | exec_printer | exec_logger,
    exec_stop = 1 << 4
} Flag_settings;

#endif // UTILS_H

#ifndef UTILS_H
#define UTILS_H

#include "circular_buffer.h"

typedef enum Processor_mode
{
    idle_mode = 0, iowait_mode, //idle
    user_mode, nice_mode, system_mode, irq_mode, softirq_mode, steal_mode,//non idle
    number_of_proccesor_modes
} Processor_mode;

#endif // UTILS_H

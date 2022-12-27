#ifndef ANALYZER_H
#define ANALYZER_H

#include "circular_buffer.h"
#include "utils.h"
#include <unistd.h>

typedef struct Components_processed_data
{
    double idle_processed_data;
    double total_proccesed_data;
} Components_processed_data;

void* analyzer_thread(void* arg);
Components_processed_data calculate_components_proccesed_data(Circular_buffer* circular_buffer);
double calculate_proccesed_data(Components_processed_data* previous, Components_processed_data* current);

#endif // ANALYZER_H

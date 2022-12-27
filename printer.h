#ifndef PRINTER_H
#define PRINTER_H

#include "circular_buffer.h"
#include "utils.h"
#include <unistd.h>

void* printer_thread(void* thread_data);

#endif // PRINTER_H

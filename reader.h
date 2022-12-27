#ifndef READER_H
#define READER_H

#include "circular_buffer.h"
#include "utils.h"
#include <unistd.h>


void* reader_thread(void* circular_buffer);
void read_proc_stat(Circular_buffer* circular_buffer);

#endif // READER_H

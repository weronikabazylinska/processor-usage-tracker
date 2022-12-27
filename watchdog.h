#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "utils.h"
#include <unistd.h>

void* watchdog_thread(void* thread_data);

#endif // WATCHDOG_H

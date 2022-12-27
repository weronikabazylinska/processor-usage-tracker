This program calculate CPU usage every second based on data from /proc/stat file.

To terminate program by catching SIGTERM type in: kill PID (PID need to by replace by process id number, this value is print by printer_tread).

Result of testing program by valgrind:

HEAP SUMMARY: in use at exit: 0 bytes in 0 blocks total heap usage: 38 allocs, 38 frees, 29,816 bytes allocated

All heap blocks were freed -- no leaks are possible

For lists of detected and suppressed errors, rerun with: -s ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

#CC = gcc
CC = clang
#CFLAGS = -Wpedantic -Wextra -Wall
CFLAGS = -Weverything -Wno-declaration-after-statement -Wno-padded -Wno-atomic-implicit-seq-cst -Wno-disabled-macro-expansion

OBJ  = output

all: main.o reader.o analyzer.o printer.o logger.o watchdog.o circular_buffer.o test.o
	$(CC) $(CFLAGS) main.o reader.o analyzer.o printer.o logger.o watchdog.o circular_buffer.o test.o -o $(OBJ)

main.o: main.c reader.h analyzer.h printer.h logger.h watchdog.h
	$(CC) $(CFLAGS) -c main.c

reader.o: reader.c reader.h circular_buffer.h utils.h
	$(CC) $(CFLAGS) -c reader.c

analyzer.o: analyzer.c analyzer.h circular_buffer.h utils.h
	$(CC) $(CFLAGS) -c analyzer.c

printer.o: printer.c printer.h circular_buffer.h utils.h
	$(CC) $(CFLAGS) -c printer.c

logger.o: logger.c logger.h utils.h
	$(CC) $(CFLAGS) -c logger.c

watchdog.o: watchdog.c watchdog.h utils.h
	$(CC) $(CFLAGS) -c watchdog.c

test.o: test.c test.h circular_buffer.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -rf output
	rm -rf *.o

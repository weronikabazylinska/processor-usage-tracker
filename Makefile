#CC = gcc
CC = clang
#CFLAGS = -Wpedantic -Wextra -Wall
CFLAGS = -Weverything

OBJ  = output

all: main.o circular_buffer.o test.o
	$(CC) $(CFLAGS) main.o circular_buffer.o test.o -o $(OBJ)

main.o: main.c circular_buffer.h
	$(CC) $(CFLAGS) -c main.c

circular_buffer.o: circular_buffer.c circular_buffer.h
	$(CC) $(CFLAGS) -c circular_buffer.c

test.o: test.c test.h circular_buffer.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -rf output
	rm -rf *.o

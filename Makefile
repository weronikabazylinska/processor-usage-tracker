#CC = gcc
CC = clang
#CFLAGS = -Wpedantic -Wextra -Wall
CFLAGS = -Weverything -Wno-declaration-after-statement

OBJ  = output

all: main.o circular_buffer.o reader.o test.o
	$(CC) $(CFLAGS) main.o circular_buffer.o reader.o test.o -o $(OBJ)

main.o: main.c circular_buffer.h
	$(CC) $(CFLAGS) -c main.c

reader.o: reader.c reader.h utils.h
	$(CC) $(CFLAGS) -c reader.c

circular_buffer.o: circular_buffer.c circular_buffer.h
	$(CC) $(CFLAGS) -c circular_buffer.c

test.o: test.c test.h circular_buffer.h
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -rf output
	rm -rf *.o

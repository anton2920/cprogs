# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = 

# Main part
all: prog
	$(CC) $(CFLAGS) main.o libs.o -o main $(LDFLAGS)

prog: main.o libs.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

libs.o: libs.c libs.h
	$(CC) $(CFLAGS) -c libs.c

clean:
	rm -f *.o main
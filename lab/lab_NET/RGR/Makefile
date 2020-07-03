# Initializing variables
CC = gcc
CFLAGS = -std=c90 -Wall -Wextra -O2
LDFLAGS = -lssh

# Main part
all: main libs
	$(CC) $(CFLAGS) main.o libs.o -o main $(LDFLAGS)

main: main.c
	$(CC) $(CFLAGS) -c main.c

libs: libs.c libs.h
	$(CC) $(CFLAGS) -c libs.c

clean:
	rm -f *.o main
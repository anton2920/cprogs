# Initializng variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 
DEBUG = -g

# Main part
all: main.o Object.o Class.o any.o
	$(CC) $(CFLAGS) main.o Object.o Class.o any.o -o main $(LDFLAGS) $(DEBUG)

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) -c main.c

Object.o: Object.c Object.h Object.r
	$(CC) $(CFLAGS) $(DEBUG) -c Object.c

Class.o: Class.c Class.h
	$(CC) $(CFLAGS) $(DEBUG) -c Class.c

any.o: any.c
	$(CC) $(CFLAGS) $(DEBUG) -c any.c

clean:
	rm -f *.o main
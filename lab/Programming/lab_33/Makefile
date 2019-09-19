# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c90
LDFLAGS = -lSTL

all: main.o
	$(CC) $(CFLAGS) main.o -o main $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o main
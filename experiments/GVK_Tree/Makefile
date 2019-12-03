# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99 -g
LDFLAGS = 

# Main part
all: main.o tree.o
	$(CC) $(CFLAGS) main.o tree.o -o main $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -f *.o main
# Initializing variables
CC = gcc
CFLAGS = -std=c90 -Wall -Wextra -O2
LDFLAGS =

# Main part
all: main

main: main.c
	$(CC) $(CFLAGS) main.c -o main $(LDFLAGS)

clean:
	rm -f *.o main

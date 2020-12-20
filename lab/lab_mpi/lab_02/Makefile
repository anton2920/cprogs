# Initializing variables
CC = mpicc
CFLAGS = -std=c90 -Wall -Wextra -O2

# Main part
all: main.c
	$(CC) $(CFLAGS) main.c -o main

clean:
	rm -f *.o main

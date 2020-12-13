# Initializing variables
CC = gcc
CFLAGS = -std=c90 -O0 -fopenmp -Wall -Wextra
LDFLAGS = -lm

# Main part
all: main.c
	$(CC) $(CFLAGS) main.c -o main $(LDFLAGS)

clean:
	rm -f *.o main
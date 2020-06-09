# Initializing variables
CC = gcc
CFLAGS = -std=c90 -Wall -Wextra -O2
LDFLAGS =

# Main part
all: main.c
	$(CC) main.c -o server $(LDFLAGS)

clean:
	rm -f *.o server
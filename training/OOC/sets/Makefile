# Initializng variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 
DEBUG = -g

# Main part
all: main.o Set.o
	$(CC) $(CFLAGS) main.o Set.o -o main $(LDFLAGS) $(DEBUG)

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) -c main.c

Set.o: Set2.c
	$(CC) $(CFLAGS) $(DEBUG) -c Set2.c -o Set.o

clean:
	rm -f *.o main
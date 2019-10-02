# Initializng variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 
DEBUG = -g

# Main part
all: main.o new.o String.o
	$(CC) $(CFLAGS) main.o new.o String.o -o main $(LDFLAGS) $(DEBUG)

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) -c main.c

new.o: new.c
	$(CC) $(CFLAGS) $(DEBUG) -c new.c

String.o: String.c
	$(CC) $(CFLAGS) $(DEBUG) -c String.c

clean:
	rm -f *.o main
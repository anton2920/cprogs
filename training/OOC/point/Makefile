# Initializng variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 
DEBUG = -g

# Main part
all: main.o new.o Point.o Circle.o
	$(CC) $(CFLAGS) main.o new.o Point.o Circle.o -o main $(LDFLAGS) $(DEBUG)

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) -c main.c

new.o: new.c new.h new.r
	$(CC) $(CFLAGS) $(DEBUG) -c new.c

Point.o: Point.c Point.h Point.r
	$(CC) $(CFLAGS) $(DEBUG) -c Point.c

Circle.o: Circle.c Circle.h Circle.h
	$(CC) $(CFLAGS) $(DEBUG) -c Circle.c

clean:
	rm -f *.o main
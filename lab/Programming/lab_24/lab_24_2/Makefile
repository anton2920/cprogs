# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c90 -O3
LDFLAGS = 

all: main.o source.o
	$(CC) $(CFLAGS) main.o source.o -o main $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

source.o: source.c
	$(CC) $(CFLAGS) -c source.c

clean:
	rm -f *.o main
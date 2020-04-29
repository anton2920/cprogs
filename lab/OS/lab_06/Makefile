# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c90
LDFLAGS = -lpthread

# Main part
all: main visual
	$(CC) $(CFLAGS) main.o libs.o -o main $(LDFLAGS)

main: main.c
	$(CC) $(CFLAGS) -c main.c

visual: libs.c libs.h
	$(CC) $(CFLAGS) -c libs.c

clean:
	rm -f *.o main
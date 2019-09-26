# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89
LDFLAGS = 
DEBUG = -g

# Main part
all: main.o libs.o
	$(CC) main.o libs.o -o main $(LDFLAGS) $(DEBUG)

main.o: main.c
	$(CC) -c main.c $(DEBUG)

libs.o: libs.c
	$(CC) -c libs.c $(DEBUG)

clean:
	rm -f *.o main
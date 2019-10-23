# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 

# Main part
all: prog
	$(CC) $(CFLAGS) main.o libs.o tree.o -o main $(LDFLAGS)

prog: main.o libs.o tree.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

libs.o: libs.c libs.h
	$(CC) $(CFLAGS) -c libs.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

clean:
	rm -f *.o main
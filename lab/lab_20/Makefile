# Initializing variables
CC = gcc
ARGS = -std=c90 -Wall
DYNAMIC = -lm -lSDL2

all: main.o tasks.o routines.o
	$(CC) $(ARGS) main.o tasks.o routines.o -o main $(DYNAMIC)

main.o:	main.c
	$(CC) $(ARGS) -c main.c

tasks.o: tasks.c
	$(CC) $(ARGS) -c tasks.c

routines.o: routines.c
	$(CC) $(ARGS) -c routines.c

clean:
	rm -f *.o main
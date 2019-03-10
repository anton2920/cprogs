# Initializing variables
CC = gcc
ARGS = -std=c90 -Wall
DYN_DEP = -lm -lSDL2 -lSDL2_image

all: main.o routines.o
	$(CC) $(ARGS) main.o routines.o -o main $(DYN_DEP)

main.o: main.c
	$(CC) $(ARGS) -c main.c

routines.o: routines.c
	$(CC) $(ARGS) -c routines.c

clean:
	rm -f *.o main
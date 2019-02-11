# Initializing variables
CC = gcc
CFLAGS = -Wall -std=c90
LINUX = -lncursesw
BSD = -lcursesw

all: prog

prog: main.o menu.o math.o tree.o menu2.o menu3.o
	$(CC) $(CFLAGS) main.o menu.o menu2.o menu3.o tree.o math.o -o main -ldialog $(LINUX) -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

menu.o: libs/menu.c
	$(CC) $(CFLAGS) -c libs/menu.c

menu2.o:libs/menu2.c
	$(CC) $(CFLAGS) -c libs/menu2.c

menu3.o: libs/menu3.c
	$(CC) $(CFLAGS) -c libs/menu3.c

math.o: libs/math.c
	$(CC) $(CFLAGS) -c libs/math.c

tree.o: libs/tree.o
	$(CC) $(CFLAGS) -c libs/tree.c
clean:
	rm -rf *o main

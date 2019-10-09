# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 

# Main part
all: prog STL
	$(CC) $(CFLAGS) main.o libs.o STL.o -o main $(LDFLAGS)

prog: main.o libs.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

libs.o: libs.c libs.h
	$(CC) $(CFLAGS) -c libs.c


# Building STL for statical linkage
STL: /home/anton/C/home/STL2/src/STL_List/STL_List.c /home/anton/C/home/STL2/src/STL_List/STL_List.h /home/anton/C/home/STL2/src/STL.h
	$(CC) $(CFLAGS) -c /home/anton/C/home/STL2/src/STL_List/STL_List.c -o ./STL.o

clean:
	rm -f *.o main
# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 

# Main part
all: main.o libs.o
	$(CC) $(CFLAGS) main.o libs.o -o main $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

libs.o: libs.c
	$(CC) $(CFLAGS) -c libs.c

clean:
	rm -f *.o main
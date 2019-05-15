# Initializing variables
CC = gcc
CFLAGS = -O3 -Wall -Wextra
LDFLAGS = 

# Main part
all: lab_25

lab_25: main.o
	$(CC) $(CFLAGS) main.o -o lab_25 $(LDFLAGS)

main.o: lab_25.c
	$(CC) $(CFLAGS) -c lab_25.c -o main.o

clean:
	rm -f *.o lab_25
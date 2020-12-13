# Initializing variables
CC = mpicc
CFLAGS = -std=c90 -Wall -Wextra -O2
LDFLAGS = -lmpi

# Main part
all: main.c
	$(CC) $(CFLAGS) main.c -o main # $(LDFLAGS)

clean:
	rm -f *.o main

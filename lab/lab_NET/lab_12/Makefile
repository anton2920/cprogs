# Initializing variables
CC = gcc
CFLAGS = -std=c90 -Wall -Wextra -O2
LDFLAGS = -lpthread

# Main part
all: client.c
	$(CC) $(CFLAGS) client.c -o client $(LDFLAGS)

clean:
	rm -f *.o client
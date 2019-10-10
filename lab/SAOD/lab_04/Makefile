# Initializing variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c89 -O2
LDFLAGS = 

# Main part
all: task STL
	$(CC) $(CFLAGS) main.o STL_List.o STL_Queue.o -o main $(LDFLAGS)

task: main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

STL: STL_List STL_Queue /home/anton/C/home/STL2/src/STL.h

STL_List: /home/anton/C/home/STL2/src/STL_List/STL_List.c /home/anton/C/home/STL2/src/STL_List/STL_List.h
	$(CC) $(CFLAGS) -c /home/anton/C/home/STL2/src/STL_List/STL_List.c -o ./STL_List.o

STL_Queue: /home/anton/C/home/STL2/src/STL_Queue/STL_Queue.c /home/anton/C/home/STL2/src/STL_Queue/STL_Queue.h
	$(CC) $(CFLAGS) -c /home/anton/C/home/STL2/src/STL_Queue/STL_Queue.c -o ./STL_Queue.o

clean:
	rm -f *.o main
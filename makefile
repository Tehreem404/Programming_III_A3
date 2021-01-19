CFLAGS = -Wall -pedantic -std=c99 -DLIST
CC = gcc

all: test1 test2 test3

test1: test1.o list.c list.h
	$(CC) $(CFLAGS) test1.o list.c -o test1

test1.o: test1.c
	$(CC) $(CFLAGS) -c test1.c -o test1.o

test2: test2.o list.c list.h
	$(CC) $(CFLAGS) test2.o list.c -o test2

test2.o: test2.c
	$(CC) $(CFLAGS) -c test2.c -o test2.o

test3: test3.o list.c list.h
	$(CC) $(CFLAGS) test3.o list.c -o test3

test3.o: test3.c
	$(CC) $(CFLAGS) -c test3.c -o test3.o

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c -o list.o

clean:
	rm *.o -i test1 test2 test3
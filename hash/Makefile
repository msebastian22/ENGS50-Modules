CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: test1 

hash.o: hash.c hash.h
	gcc $(CFLAGS) -c hash.c

test1.o: test1.c hash.h
	gcc $(CFLAGS) -c test1.c

test1: test1.o hash.o
	gcc $(CFLAGS) test1.o hash.o -o test1

clean:
	rm -f *.o test1

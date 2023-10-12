CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: queue_test1 queue_test2 queue_test3 queue_test4 

hash.o: hash.c hash.h
	gcc $(CFLAGS) -c hash.c

queue_test1.o: queue_test1.c hash.h
	gcc $(CFLAGS) -c queue_test1.c

queue_test2.o: queue_test2.c hash.h
	gcc $(CFLAGS) -c queue_test2.c

queue_test3.o: queue_test3.c hash.h
	gcc $(CFLAGS) -c queue_test3.c

queue_test4.o: queue_test4.c hash.h
	gcc $(CFLAGS) -c queue_test4.c

queue_test1: queue_test1.o hash.o
	gcc $(CFLAGS) queue_test1.o hash.o -o queue_test1

queue_test2: queue_test2.o hash.o
	gcc $(CFLAGS) queue_test2.o hash.o -o queue_test2

queue_test3: queue_test3.o hash.o
	gcc $(CFLAGS) queue_test3.o hash.o -o queue_test3

queue_test4: queue_test4.o hash.o
	gcc $(CFLAGS) queue_test4.o hash.o -o queue_test4


clean:
	rm -f *.o queue_test1 queue_test2 queue_test3 queue_test4 

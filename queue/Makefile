CFLAGS=-Wall -pedantic -std=c11 -I. -g

all: queue_test1

queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

queue_test1.o: queue_test1.c queue.h
	gcc $(CFLAGS) -c queue_test1.c



queue_test1: queue_test1.o queue.o
	gcc $(CFLAGS) queue_test1.o queue.o -o queue_test1

clean:
	rm -f *.o queue_test1

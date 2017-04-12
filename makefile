linked_queue: main.o linked_queue.o
	gcc -lm -o linked_queue main.o linked_queue.o

main.o: main.c linked_queue.h
	gcc -c main.c


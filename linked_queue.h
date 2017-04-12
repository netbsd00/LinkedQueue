#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "packet_data_type.h"

typedef struct _note_t
{
    void *data;
    struct _note_t *next;
} node_t;

typedef struct _linked_queue_t
{
	node_t *front;
	node_t *rear;
	INT32 count;

	void (*f_release_data)(void *);
	void (*f_push)(struct _linked_queue_t *, void*);
	void *(*f_pop)(struct _linked_queue_t *);
	INT32 (*f_size)(struct _linked_queue_t *);
} linked_queue_t;

linked_queue_t *queue_create(void (*release)(void *));
void queue_destroy(linked_queue_t *q);

void printQueueDump(linked_queue_t *q);
#endif //LINKED_QUEUE_H


/*
 * linked_queue.c
 *
 *  Created on: 2017.04.07
 *      Author: hwyi
 */
#include <stdio.h>
#include <stdlib.h>
#include "linked_queue.h"

#define PRIV_DATA(q)	((private_data_t *)q->_priv_data)

static void queue_init(linked_queue_t *q, void (*release)(void *));
static void queue_push(linked_queue_t *q, void *data);
static void *queue_pop(linked_queue_t *q);
static INT32 queue_size(linked_queue_t *q);

typedef struct _note_t
{
    void *data;
    struct _note_t *next;
} node_t;

typedef struct _private_data_t {
	node_t *front;
	node_t *rear;
	INT32 count;
} private_data_t;

linked_queue_t *queue_create(void (*release)(void *)) {
	linked_queue_t *q = malloc(sizeof(linked_queue_t));
	if(q != NULL) {
		private_data_t *priv_data = malloc(sizeof(private_data_t));
		if(priv_data != NULL) {
			q->_priv_data = priv_data;
			queue_init(q, release);
			return q;	
		}
	}

	return NULL;
}

void queue_destroy(linked_queue_t *q) {
	if(q != NULL && PRIV_DATA(q)->front != NULL) {
		node_t *temp;
		do {
			if(PRIV_DATA(q)->front->data != NULL) {
				if(q->f_release_data != NULL) {
					q->f_release_data(PRIV_DATA(q)->front->data);
				}
				free(PRIV_DATA(q)->front->data);
			}

			temp = PRIV_DATA(q)->front->next;
			free(PRIV_DATA(q)->front);
			PRIV_DATA(q)->front = temp;
		} while(PRIV_DATA(q)->front);
		free(q->_priv_data);
		free(q);
	}
}

static void queue_init(linked_queue_t *q, void (*release)(void *)) {
	if(q != NULL) {
		PRIV_DATA(q)->front = PRIV_DATA(q)->rear = NULL;
		PRIV_DATA(q)->count = 0;

		q->f_release_data = release;
		q->f_push = queue_push;
		q->f_pop = queue_pop;
		q->f_size = queue_size;
	}
}

static INT32 queue_size(linked_queue_t *q) {
	return (q != NULL) ? PRIV_DATA(q)->count : -1;
}

static void queue_push(linked_queue_t *q, void *data) {
	if(q != NULL) {
		node_t *new_node = (node_t *)malloc(sizeof(node_t));
		if(new_node != NULL) {
			if (PRIV_DATA(q)->rear == NULL) {
				PRIV_DATA(q)->rear = new_node;
				PRIV_DATA(q)->rear->next = NULL;
				PRIV_DATA(q)->rear->data = data;
				PRIV_DATA(q)->front = PRIV_DATA(q)->rear;
			} else {
				PRIV_DATA(q)->rear->next = new_node;
				new_node->data = data;
				new_node->next = NULL;

				PRIV_DATA(q)->rear = new_node;
			}
			PRIV_DATA(q)->count++;				
		}
	}
}

static void *queue_pop(linked_queue_t *q) {
	void *data = NULL;
	
	if (PRIV_DATA(q)->front != NULL) {
		if (PRIV_DATA(q)->front->next != NULL) {
			node_t *temp;

			temp = PRIV_DATA(q)->front->next;
			data = PRIV_DATA(q)->front->data;
			free(PRIV_DATA(q)->front);
			PRIV_DATA(q)->front = temp;
		} else {
			data = PRIV_DATA(q)->front->data;
			free(PRIV_DATA(q)->front);
			PRIV_DATA(q)->front = NULL;
			PRIV_DATA(q)->rear = NULL;
		}
		PRIV_DATA(q)->count--;
	}
	return data;
}

void printQueueDump(linked_queue_t *q) {
	if(q != NULL) {
		printf("\n===  QUEUE DUMP === \n");
		printf(" size = %d\n", q->f_size(q));
		printf("=================== \n");

		node_t *temp = PRIV_DATA(q)->front;
		node_t *n;
		packet_t *pkt;
		while(PRIV_DATA(q)->front) {
			n = PRIV_DATA(q)->front;
			pkt = n->data;
			printf("%s   ", pkt->data);
			PRIV_DATA(q)->front = n->next;
		}
		printf("\n====== END ======== \n");
		PRIV_DATA(q)->front = temp;
	}
}

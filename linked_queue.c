/*
 * linked_queue.c
 *
 *  Created on: 2017.04.07
 *      Author: hwyi
 */
#include <stdio.h>
#include <stdlib.h>
#include "linked_queue.h"

static void queue_init(linked_queue_t *q, void (*release)(void *));
static void queue_push(linked_queue_t *q, void *data);
static void *queue_pop(linked_queue_t *q);
static INT32 queue_size(linked_queue_t *q);


linked_queue_t *queue_create(void (*release)(void *)) {
	linked_queue_t *q = malloc(sizeof(linked_queue_t));
	if(q != NULL) {
		queue_init(q, release);
		return q;
	}

	return NULL;
}

void queue_destroy(linked_queue_t *q) {
	if(q != NULL && q->front != NULL) {
		node_t *temp;

		do {
			if(q->front->data != NULL) {
				if(q->f_release_data != NULL) {
					q->f_release_data(q->front->data);
				}
				free(q->front->data);
			}

			temp = q->front->next;
			free(q->front);
			q->front = temp;
		} while(q->front);

		free(q);
	}
}

static void queue_init(linked_queue_t *q, void (*release)(void *)) {
	if(q != NULL) {
		q->front = q->rear = NULL;
		q->count = 0;

		q->f_release_data = release;
		q->f_push = queue_push;
		q->f_pop = queue_pop;
		q->f_size = queue_size;
	}
}

static INT32 queue_size(linked_queue_t *q) {
	return (q != NULL) ? q->count : -1;
}

static void queue_push(linked_queue_t *q, void *data) {
	if(q != NULL) {
		if (q->rear == NULL) {
			q->rear = (node_t *)malloc(sizeof(node_t));
			q->rear->next = NULL;
			q->rear->data = data;
			q->front = q->rear;
		} else {
			node_t *temp = (node_t *)malloc(sizeof(node_t));
			q->rear->next = temp;
			temp->data = data;
			temp->next = NULL;

			q->rear = temp;
		}
		q->count++;	
	}
}

static void *queue_pop(linked_queue_t *q) {
	void *data = NULL;
	
	if (q->front != NULL) {
		if (q->front->next != NULL) {
			node_t *temp;

			temp = q->front->next;
			data = q->front->data;
			free(q->front);
			q->front = temp;
		} else {
			data = q->front->data;
			free(q->front);
			q->front = NULL;
			q->rear = NULL;
		}
		q->count--;
	}
	return data;
}

void printQueueDump(linked_queue_t *q) {
	if(q != NULL) {
		printf("\n===  QUEUE DUMP === \n");
		printf(" size = %d\n", q->f_size(q));
		printf("=================== \n");

		node_t *temp = q->front;
		node_t *n;
		packet_t *pkt;
		while(q->front) {
			n = q->front;
			pkt = n->data;
			printf("%s   ", pkt->data);
			q->front = n->next;
		}
		printf("\n====== END ======== \n");
		q->front = temp;
	}
}

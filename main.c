#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_queue.h"

static void release_queue_data(void *pkt) {
	if(pkt != NULL) {
		packet_t *p = pkt;
		if(p->data != NULL) {
			free(p->data);
		}
	}
}

int main(void) {
	linked_queue_t *queue = queue_create(release_queue_data);
	packet_t *pkt;
	
	pkt = malloc(sizeof(packet_t));
	pkt->cmd = 0;
	pkt->data = malloc(3);
	memcpy(pkt->data, "ABC", 3);
	pkt->data_len = 3;
	
	queue->f_push(queue, pkt);
	
	pkt = malloc(sizeof(packet_t));
	pkt->cmd = 0;
	pkt->data = malloc(4);
	memcpy(pkt->data, "DEFG", 4);
	pkt->data_len = 4;
	
	queue->f_push(queue, pkt);

	pkt = malloc(sizeof(packet_t));
	pkt->cmd = 0;
	pkt->data = malloc(2);
	memcpy(pkt->data, "HI", 2);
	pkt->data_len = 2;
	
	queue->f_push(queue, pkt);
	
	printQueueDump(queue);
	
	queue->f_pop(queue);
	printQueueDump(queue);

	queue_destroy(queue);
	return 0;
}

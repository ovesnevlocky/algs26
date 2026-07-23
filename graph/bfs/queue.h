#ifndef QUEUE_H_
#define QUEUE_H_


#include "node.h"
#include "stdbool.h"
#include "bfs.h"
typedef struct
{
	node_t arr[MAX_SIZE];
	int head;
	int tail;
	int count;
}Queue;


void printhai();

void queueInit(Queue *q);

bool isQueueEmpty(Queue *q);

bool isQueueFull(Queue *q);

bool pushQueue(Queue *q, node_t a);

node_t popQueue(Queue *q);

node_t peekQueue(Queue *q);

void printQueue(const Queue q);

#endif



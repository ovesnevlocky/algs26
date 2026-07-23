#include <stdio.h>
#include "queue.h"
#include <string.h>

#include "bfs.h"

#include "../graph.h"

void printhai()
{
	printf("hello from queue\n");
}

void queueInit(Queue *q)
{
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	memset(q->arr, 0, sizeof(node_t)* MAX_SIZE);
}

bool isQueueEmpty(Queue *q)
{
	return q->count <= 0;
}

bool isQueueFull(Queue *q)
{
	return q -> count > MAX_SIZE;
}

bool pushQueue(Queue *q, node_t a)
{
	if(isQueueFull(q))
	{
		printf("queue is full Max: %i, Current: %i\n", MAX_SIZE, q->count);
		return false;
	}

	q->arr[q->tail] = a;
	
	q->tail += 1;
	q-> count += 1;

	return true;
}

node_t popQueue(Queue *q)
{
	node_t ret = {0};
		ret.edgeStart = -1;

	if(isQueueEmpty(q))
	{
		puts("queue is empty");
		return ret;
	}

	ret = q->arr[q->head];
	//change tag to indicate non active element
	q->arr[q->head].edgeStart = -1;
	q->head += 1;
	q-> count -= 1;

	return ret;
}

node_t peekQueue(Queue *q)
{
	node_t ret = {0};
	ret.edgeStart = -1;	
	if(isQueueEmpty(q))
	{
		printf("queue is empty");
		return ret;	
	}

	return q->arr[q->head];
}

void printQueue(const Queue q)
{
	int count  = q.count;
	int head = q.head;

	node_t tmp = {0};
	while(count > 0)
	{
		tmp = q.arr[head];
		count--;
		head++;
	}

	putchar('\n');
}

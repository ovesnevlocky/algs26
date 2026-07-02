#include <stdio.h>
#include "queue.h"

void printhai()
{
	printf("hello from queue\n");
}

void queueInit(Queue *q)
{
	q->head = 0;
	q->tail = 0;
	q->count = 0;
}

bool isQueueEmpty(Queue *q)
{
	return q->count <= 0;
}

bool isQueueFull(Queue *q)
{
	return q -> count > MAX_SIZE;
}

bool pushQueue(Queue *q, var a)
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

var popQueue(Queue *q)
{
	var ret = {0};
	ret.tag = UNINICIALIZED;	

	if(isQueueEmpty(q))
		return ret;

	ret = q->arr[q->head];
	//change tag to indicate non active element
	q->arr[q->head].tag = UNINICIALIZED;
	q->head += 1;
	q-> count -= 1;

	return ret;
}

var peek(Queue *q)
{
	var ret = {0};
	ret.tag = UNINICIALIZED;	
	if(isQueueEmpty(q))
	{
		printf("queue is empty\n");
		return ret;	
	}

	return q->arr[q->head];
}

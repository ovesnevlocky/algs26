#ifndef STACK_H_
#define STACK_H_

#define ARR_EMPTY (-1)
#define MAX_SIZE 100
#include <stdbool.h>
#include "bfs.h"
#include "graph.h"


typedef struct
{
	node_t arr[MAX_SIZE];
	int top;
	int count;
}Stack;

void stackInit(Stack *s);

bool isStackFull(Stack *s);

bool isStackEmpty(Stack *s);

bool stackPush(Stack *s, node_t a);

node_t stackPeek(Stack *s);

node_t  stackPop(Stack *s);
void hellostack();

void stackPrint(const Stack s);

#endif

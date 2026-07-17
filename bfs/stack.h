#ifndef STACK_H_
#define STACK_H_

#define MAX_SIZE 100
#include <stdbool.h>

#include "token.h"

typedef struct
{
	var arr[MAX_SIZE];
	int top;
	int count;
}Stack;

void stackInit(Stack *s);

bool isStackFull(Stack *s);

bool isStackEmpty(Stack *s);

bool stackPush(Stack *s, var a);

var stackPeek(Stack *s);

var  stackPop(Stack *s);
void hellostack();

void stackPrint(const Stack s);

#endif

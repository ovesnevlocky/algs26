#include <stdio.h>

#include <stdlib.h>

#include "stack.h"

void hellostack()
{
	printf("helo from stack\n");
}

void stackInit(Stack *s)
{
	s->top = -1;
	s->count = 0;
}

bool isStackFull(Stack *s)
{
	return s->count >= MAX_SIZE;
}

bool isStackEmpty(Stack *s)
{
	return s-> count <= 0;
}

bool stackPush(Stack *s, var a)
{
	if(isStackFull(s))
	{
		printf("stack is full MAX: %i, current %i\n", MAX_SIZE, s->count);
		return false;
	}
	
	if(a.tag == UNINICIALIZED)
	{
		printf("token is not inicialized\n");
		return false;
	}
	
	//has to be incremented first, as inicialized -1
	s->top += 1;
	s->count += 1;
	s->arr[s->top] = a;

	return true;
}
       
var stackPeek(Stack *s)
{
	return s->arr[s->top];
}

var stackPop(Stack *s)
{

	var ret = {0};
	
	ret.tag = UNINICIALIZED;
	if(isStackEmpty(s))
		return ret;

	ret = s->arr[s->top];

	//set uninicialized to indicate non active element
	s->arr[s->top].tag = UNINICIALIZED;
	s->top -= 1;
	s->count -= 1;
	
	return ret;
}


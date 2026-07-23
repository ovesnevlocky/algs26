#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include "stack.h"

void hellostack()
{
	printf("helo from stack\n");
}

void stackInit(Stack *s)
{
	s->top = -1;
	s->count = 0;
	memset(s->arr, 0, sizeof(node_t) * MAX_SIZE);
}

bool isStackFull(Stack *s)
{
	return s->count >= MAX_SIZE;
}

bool isStackEmpty(Stack *s)
{
	return s-> count <= 0;
}

bool stackPush(Stack *s, node_t a)
{
	if(isStackFull(s))
	{
		printf("stack is full MAX: %i, current %i\n", MAX_SIZE, s->count);
		exit(-1);
		return false;
	}
	
	if(a.edgeStart == -1)
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
       
node_t stackPeek(Stack *s)
{
	node_t ret = {0};
	//if not a element is in the stack
	if(s-> top < 0)
	{
		ret.edgeStart = ARR_EMPTY;
		return ret; 
	}
	 
	return s->arr[s->top];
}

node_t stackPop(Stack *s)
{

	node_t ret = {0};
	
	ret.edgeStart = -1;
	if(isStackEmpty(s))
		return ret;

	ret = s->arr[s->top];

	//set uninicialized to indicate non active element
	s->arr[s->top].edgeStart = -1;
	s->top -= 1;
	s->count -= 1;
	
	return ret;
}

void stackPrint(const Stack s)
{
	int tmpTop = s.top;
	int count = s.count;
	node_t tmp = {0};

	while(count > 0)
	{
		tmp = s.arr[tmpTop];
		tmpTop--;		
		count--;
	}

}

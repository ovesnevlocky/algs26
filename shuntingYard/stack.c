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
	memset(s->arr, 0, sizeof(var) * MAX_SIZE);
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
	var ret = {0};
	ret.tag = UNINICIALIZED;
	if(s-> top < 0)
		return ret; 
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

void stackPrint(const Stack s)
{
	int tmpTop = s.top;
	int count = s.count;
	var tmp = {0};

	while(count > 0)
	{
		tmp = s.arr[tmpTop];
		printMem(tmp);
		tmpTop--;		
		count--;
	}

}

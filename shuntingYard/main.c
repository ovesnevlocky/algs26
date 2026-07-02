#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "token.h"
#include <stdlib.h>


bool isOp(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void printMem(var v)
{
	switch(v.tag)
	{
		case UNINICIALIZED: 
		      puts("uninicialized");
		      break;
		case INT:
		      printf("popped: %i\n", v.data.var);
		      break;
		case CHAR:
		      printf("pooped: %c\n", v.data.operand);
		      break;
		default: 
		      puts("unkonown value");
		      break;
	
	}
}

//function to get how many digits 
int digits(int a)
{
	int ret = 0;
	if(a == 0)
		return 0;
	while(a > 0)
	{
		a = a/ 10;
		ret++;
	}

	return ret;

}

void perseData(Queue *inputQ, char *str)
{
	char *ptr_s = str;
	//Iterate until get to the null char
	while(*ptr_s)
	{
		var tmp = {0};

		if(isOp(*ptr_s))
		{
			tmp.tag = CHAR;
			tmp.data.operand = *ptr_s;
			pushQueue(inputQ, tmp);
			//increment for this char 
			ptr_s++;
		}
		else
		{
			int var = atoi(ptr_s);
			tmp.tag = INT;
			tmp.data.var = var; 
			pushQueue(inputQ, tmp);
			int size = digits(var);
			//increment as many as the var has digits
			ptr_s += size;	
		}
		//skip a white space
		ptr_s++;
	}
}

int main()
{

	char *str = "1 + 2 + 3 * 23432 + 2345 + 654";
	Queue inputQ;
	queueInit(&inputQ);
	
	perseData(&inputQ, str);

	while(!isQueueEmpty(&inputQ))
	{
		var ret = popQueue(&inputQ);
		printMem(ret);
	
	}

	return 0;
}

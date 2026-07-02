#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "token.h"
#include <stdlib.h>


bool isOp(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


int getPrecedence(char ch)
{
	switch(ch)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			puts("unknown operator");
			return -1;
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

void parseData(Queue *inputQ, char *str)
{
	char *ptr_s = str;
	//Iterate until get to the null char
	while(*ptr_s)
	{
		var tmp = {0};

		if(isOp(*ptr_s))
		{
			tmp.tag = CHAR;
			//get precedence according to operator
			tmp.data.op.precedence = getPrecedence(*ptr_s);
			//record the original operator
			tmp.data.op.op = *ptr_s;
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

Queue getSolveStack(Queue *inputQ)
{
	Queue ret;
	queueInit(&ret);

	Stack holdingS;
	stackInit(&holdingS);

	Queue outQ;
	queueInit(&outQ);

	while(!isQueueEmpty(inputQ))
	{
		var tmp = popQueue(inputQ);
		if(tmp.tag == CHAR)
		{
			return ret;	
		
		}else if(tmp.tag == INT)
		{
			return ret;
		}
	
	}

	return ret;
}


int main()
{

	char *str = "1 + 2 + 3 * 23432 + 2345 + 654 + 23 + 2343 - 2 / 3";

	//queue for input string
	Queue inputQ;
	queueInit(&inputQ);

	parseData(&inputQ, str);
	
	printQueue(inputQ);


	Queue solveS = getSolveStack(&inputQ);

	return 0;
}




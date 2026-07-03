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

Queue getOutQ(Queue *inputQ)
{
	Stack holdS;
	stackInit(&holdS);

	Queue outQ;
	queueInit(&outQ);
	
	while(!isQueueEmpty(inputQ))
	{
		var popped = popQueue(inputQ);
			
		if(popped.tag == INT)
		{
			pushQueue(&outQ, popped);		
		}
		else if(popped.tag == CHAR)
		{
			//first peek inputQ
			//lets say A is the element about to push
			//         B is the element on top of stack
			//if A's precedence is higher than that of B,  push
			//otherwise pop and push to the outQ
			//until the condition matches, if A's precedence becames higher
			//than  that of B then stop and push A to the outQ 
			var peekedOp = stackPeek(&holdS);
			
			if(peekedOp.tag == ARR_EMPTY)
			{
				stackPush(&holdS, popped);
			}
			else if(popped.data.op.precedence > peekedOp.data.op.precedence)
			{
					stackPush(&holdS, popped);
			}
			else
			{
				while(popped.data.op.precedence <= peekedOp.data.op.precedence)
				{
					var poppedOp = stackPop(&holdS);
					pushQueue(&outQ, poppedOp);
					peekedOp = stackPeek(&holdS);
				}
				stackPush(&holdS,  popped);
			}
		}
	}

	//pop all the operators from holding stack
	while(!isStackEmpty(&holdS))
	{
		var popped = stackPop(&holdS);
		if(popped.tag == UNINICIALIZED)
		{
			printf("uninicialized element was popped\n");
		}
		pushQueue(&outQ, popped);
		
	}
	return outQ;
	
}

int getSolution(Queue *outQ)
{
	Stack solve
	

}


int main()
{

	char *str = "1 + 2 * 4 - 3";
	//char *str = "1 + 2 * 4 - 3 * 2 - 1";
	//char *str = "12 + 3 * 4 - 5 * 6 + 8 / 2 * 3 - 1 + 9 * 2 - 7 + 4 * 5";
	//queue for input string
	Queue inputQ;
	queueInit(&inputQ);
	
	parseData(&inputQ, str);
	//printQueue(inputQ);

	Queue outQ = getOutQ(&inputQ);
	printQueue(outQ);

	return 0;
}




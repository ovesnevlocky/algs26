#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "token.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"



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
		case '(':
		case ')':
			return 0;
		case '^':
			return 3;
		default:
			puts("unknown operator");
			return -1;
	}
}


Queue parseData(const char *str)
{
	Queue inputQ;
	queueInit(&inputQ);

	int idx = 0;
	size_t len = strlen(str);
	char buff[64] = {0};
	
	//Iterate until get to the null char
	while(cutS(str, &idx, buff) > 0)
	{
		var tmp = {0};

		if( ( buff[0] == '-' && isdigit(buff[1]) )
		    || isdigit(buff[0]))
		{
			int var = atoi(buff);
			tmp.tag = INT;
			tmp.data.var = var; 
			pushQueue(&inputQ, tmp);
		}
		else if( isOp(buff[0]) || isBracket(buff[0] ) )
		{
			tmp.tag = CHAR;
			//get precedence according to operator
			tmp.data.op.precedence = getPrecedence(buff[0]);
			//record the original operator
			tmp.data.op.op = buff[0];
			pushQueue(&inputQ, tmp);
		}
		else
		{
			printf("unkonown char\n");
		}

		//reset the buff
		memset(buff, 0, sizeof(buff));		
		if(idx > len)
			break;
		
	}
	return inputQ;
}

void popUntil(var popped, var peekedOp, Stack *holdS, Queue *outQ)
{
	while(popped.data.op.precedence <= peekedOp.data.op.precedence)
	{
		var poppedOp = stackPop(holdS);
		pushQueue(outQ, poppedOp);
		peekedOp = stackPeek(holdS);
	}
	stackPush(holdS,  popped);

}

void popToOpenBracket(Stack *holdS, Queue *outQ)
{
	var peeked = stackPeek(holdS);

	while(!isOpenB(peeked.data.op.op))
	{
		var popped = stackPop(holdS);
		
		pushQueue(outQ, popped);
		peeked = stackPeek(holdS);

	}
	//pop the close bracket
	peeked = stackPop(holdS);
	return;

}


Queue getOutQ(Queue *inputQ)
{
	Stack holdS;
	stackInit(&holdS);

	Queue outQ;
	queueInit(&outQ);
	bool isInBracket = false;	
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
			//if A's precedence is higher than that of B, push
			//otherwise pop and push to the outQ
			//until the condition matches, if A's precedence becames higher
			//than  that of B then stop and push A to the outQ 
			var peekedOp = stackPeek(&holdS);
			if(isOpenB(popped.data.op.op))
			{	
				stackPush(&holdS, popped);
				continue;
			}	
			else if(isCloseB(popped.data.op.op))
			{
				popToOpenBracket(&holdS, &outQ);
				continue;
			}

			if(peekedOp.tag == ARR_EMPTY
		          ||  isOpenB(peekedOp.data.op.op)
			  || ( isLeftToRight(popped.data.op.op) &&
					popped.data.op.precedence > peekedOp.data.op.precedence)
			  || (isRightToLeft(popped.data.op.op) &&
					popped.data.op.precedence <= peekedOp.data.op.precedence)
			                                                                          )
			{
				stackPush(&holdS, popped);
			}
			else
			{
				popUntil(popped, peekedOp, &holdS, &outQ);
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
	Stack solve;
	stackInit(&solve);

	while(!isQueueEmpty(outQ))
	{
		var popped = popQueue(outQ);
		if(popped.tag == INT)
		{
			stackPush(&solve, popped);
		}
		else if(popped.tag == CHAR)
		{
			var operand1 = stackPop(&solve);
			var operand2 = stackPop(&solve);
			var varToPush = {0};
			varToPush.tag = INT;
			varToPush.data.var = calculate(popped.data.op.op, operand2.data.var, operand1.data.var);
			stackPush(&solve, varToPush);
		}
	}

	return solve.arr[0].data.var;
}


int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char *str = NULL;
	
	if(argc > 1)
	{
		fp = fopen(argv[1], "r");
		if(!fp)
		{
			printf("error in opening the file");
			exit(1);
		}

		size_t size = 0;
		size_t len = getline(&str, &size, fp);
	}
	else 
		str = "3 + 3 ^ 3 + ( 3 )";

	//queue for input string
	Queue inputQ = parseData(str);
	//printQueue(inputQ);

	Queue outQ = getOutQ(&inputQ);
	printQueue(outQ);

	int ret = getSolution(&outQ);
	
	printf("%i\n",ret); 
	if(fp)
	{
		free(str);
		fclose(fp);
	}
	return 0;
}




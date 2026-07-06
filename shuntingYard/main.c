#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "token.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


bool isOp(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isBracket(char ch)
{
	return ch == '(' || ch == ')';
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
		case '(':
		case ')':
			return 3;
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
	int idx = 0;
	size_t len = strlen(str);
	//Iterate until get to the null char
	while(*ptr_s)
	{
		var tmp = {0};
		if(idx > len)
			break;
		if(isOp(*ptr_s) || isBracket(*ptr_s))
		{
			tmp.tag = CHAR;
			//get precedence according to operator
			tmp.data.op.precedence = getPrecedence(*ptr_s);
			//record the original operator
			tmp.data.op.op = *ptr_s;
			pushQueue(inputQ, tmp);
			//increment for this char 
			ptr_s++;
			idx++;
		}
		else if(isdigit(*ptr_s))
		{
			int var = atoi(ptr_s);
			tmp.tag = INT;
			tmp.data.var = var; 
			pushQueue(inputQ, tmp);
			int size = digits(var);
			//increment as many as the var has digits
			ptr_s += size;	
			idx += size;
		}
		else
		{
			printf("unkonown char %c\n", *ptr_s);
			ptr_s++;
			idx++;	
		}		
		//skip a white space
		ptr_s++;
		idx++;
	}
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
			//if A's precedence is higher than that of B, push
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

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int multiply(int a, int b)
{
	if(a == 0 || b == 0)
		return 0;

	return a * b;
}
int devide(int a, int b)
{
	if(a == 0)
		return 0;

	if(b == 0)
	{	
		printf("deviding by 0 is not allowed");
		return 0;
	}


	return a / b;
}

int calculate(char op, int a, int b)
{
	int ret;
	switch(op)
	{
		case '+':
		return add(a, b);
		case '-':
		return sub(a, b);
		case '*':
		return multiply(a, b);
		case '/':
		return devide(a, b);
		default: 
			printf("unkonown operator %c\n", op);
			return -1;
	}

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


int main()
{

//	char *str = "1 + 2 * 4 - 3";
	char *str = "1 + 2 * 4 - ( 3 * 2 ) - 1";
	//char *str = "12 + 3 * 4 - 5 * 6 + 8 / 2 * 3 - 1 + 9 * 2 - 7 + 4 * 5";
	//char *str = "20 + 6 * 3 - 4 * 8 + 15 / 5 * 2 - 9 + 7 * 3 - 2 * 6 + 10 / 2 - 8 + 3 * 4";
	//queue for input string
	Queue inputQ;
	queueInit(&inputQ);
	
	parseData(&inputQ, str);
	printQueue(inputQ);

	Queue outQ = getOutQ(&inputQ);
	printQueue(outQ);

	int ret = getSolution(&outQ);
	
	printf("res %i\n",ret); 
	return 0;
}




#include <stdio.h>
#include "utils.h"


#include <stdbool.h>

bool isOp(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch =='/';
}

bool isOpenB(char ch)
{
	return ch == '(';
}
bool isCloseB(char ch)
{
	return ch == ')';
}

bool isBracket(char ch)
{
	return isOpenB(ch) || isCloseB(ch);
}

int digits(int a)
{
	int ret = 0;
	if(a == 0)
		return 0;

	while(a > 0)
	{
		a = a/10;
		ret++;
	}

	return ret;
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
		printf("deviding by 0 is not allowed\n");
		return 0;
	}

	return a/b;
}

int calculate(char op, int a, int b)
{
	int ret;
	switch(op)
	{
		case '+':
		return add(a,b);
		case '-':
		return sub(a, b);
		case '*':
		return multiply(a, b);
		case '/':
		return devide(a, b);
		default:
		printf("unknown operator %c\n", op);
		return -1;	
	}

	return -1;
}



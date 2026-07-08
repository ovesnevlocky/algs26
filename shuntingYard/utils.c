#include <stdio.h>
#include "utils.h"


#include <stdbool.h>


bool isRightToLeft(char ch)
{
	return ch == '^';
}

bool isLeftToRight(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || isUnaryOp(ch);
}

bool isUnaryOp(char ch)
{
	return ch == '!';
}
bool isOp(char ch)
{
	return isRightToLeft(ch) || isLeftToRight(ch) || isUnaryOp(ch);
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

int factorial(int a)
{
	if(a > 12)
	{
		printf("factorial more than 12 is bigger than MAX_INT\n");
		return -1;
	}
	int factorials[13] = 
	{
		0, 1, 2, 6, 24, 120, 720, 5040, 40320,
	        362880, 3628800, 39916800, 479001600       
	};

	
	return factorials[a];
	
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
		case '^':
		return getExp(a, b);
		case '!':
		return factorial(a);
		default:
		printf("unknown operator %c\n", op);
		return -1;	
	}

	return -1;
}

int cutS(const char *str, int *idx, char buff[64])
{
	int offset = 0;
	if(str[*idx] == '\0')
		return -1;

	while(*str)
	{
		if(str[*idx] == ' ' || str[*idx] == '\0') 
		{
			buff[offset] = '\0';
			*idx += 1;
			return offset;
		}
		else
		{
			buff[offset++] = str[*idx];
			*idx += 1;
		}
	}

}

int getExp(int base, int exp)
{
	int ret = 1;

	if(base == 1 || exp == 0)
		return 1;

	if(base == 0)
		return 0;


	for(int i = 0; i < exp; i++)
	{
		ret *= base;
	}

	return ret;
}

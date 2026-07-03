#ifndef TOKEN_H
#define TOKEN_H

typedef enum varType
{
	UNINICIALIZED = 0,
	ARR_EMPTY = 1,
	INT = 10,
	CHAR = 11
}varType;

typedef struct
{
	char op;
	int precedence;
	
}operator;

typedef struct 
{
	varType tag;
	union
	{
		int var;
		operator op;
	}data;

}var;

void printMem(var a);
#endif

#ifndef TOKEN_H
#define TOKEN_H

typedef enum varType
{
	UNINICIALIZED = 0,
	INT = 10,
	CHAR = 11
}varType;

typedef struct 
{
	varType tag;
	union
	{
		int var;
		char operand;
	}data;

}var;

#endif

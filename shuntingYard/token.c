#include <stdio.h>

#include "token.h"

void printMem(var a)
{
	switch(a.tag)
	{
		case UNINICIALIZED:
			puts("uninicialized");
			break;
		case INT:
			printf("%i\n", a.data.var);
			break;
		case CHAR:
			printf("%c\n", a.data.op.op);
			break;
		default:
			printf("unknown tag: %i\n", a.tag);
			break;
	
	}
}

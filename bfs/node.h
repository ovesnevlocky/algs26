#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#define MAX_SIZE 25


typedef struct
{
	int edgeStart;
	int edgeCount;
	bool isVisited;
	int nodeId;
}node_t;


#endif

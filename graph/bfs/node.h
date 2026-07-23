#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

typedef struct
{
	int edgeStart;
	int edgeCount;
	bool isVisited;
	int nodeId;
}node_t;


#endif

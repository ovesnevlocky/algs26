#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <stdbool.h>
#include "defines.h"

typedef struct
{
	int from;
	int to;
	int cost;
}edge_t;

typedef struct
{
	edge_t *edges;
	int numEdges;
	int capacity;
}graph_t;

void* myMalloc(size_t size);

graph_t * allocateGraph(void);


graph_t* enlargeGraph(graph_t *g);

int loadGraph(graph_t *g,const char *fname);

void printGraph(const graph_t *g);

void printEdges(graph_t *g);


#endif

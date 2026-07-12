#ifndef GRAPH_H
#define GRAPH_H
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100
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

typedef struct
{
	int edgeStart;
	int edgeCount;
	bool isVisited;
	
}node_t;

typedef struct
{
	//pointer to a graph
	graph_t *graph;
	//array of edges
	node_t *nodes;
	int numNodes;	
}bfs_t;

void* myMalloc(size_t size);

graph_t * allocateGraph(void);

void freeGraph(bfs_t **g);

graph_t* enlargeGraph(graph_t *g);

void printGraph(const graph_t *g);

bfs_t *createBfs(void);

void nodesInit(bfs_t *b);

void addEdgeToNodes(bfs_t *b);

int loadGraph(graph_t *g,const char *fname);
#endif

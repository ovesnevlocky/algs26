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
	//array of nodes 
	node_t *nodes;
	int numNodes;	
}bfs_t;

void* myMalloc(size_t size);

graph_t * allocateGraph(void);

bfs_t *createBfs(void);

graph_t* enlargeGraph(graph_t *g);

int loadGraph(graph_t *g,const char *fname);

void nodesInit(bfs_t *b);

void addEdgeToNodes(bfs_t *b);

void printGraph(const graph_t *g);

void printGraphNodes(const bfs_t *b);

void freeGraph(bfs_t **g);

void printNodes(bfs_t *b);

void printEdges(graph_t *g);

int *startBfs(bfs_t *b, int nodeId);

#endif

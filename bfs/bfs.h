#ifndef BFS_H
#define BFS_H

#include "node.h"
#include "queue.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	graph_t *graph;
	node_t *nodes;
	int numNodes;
}bfs_t;

void printGraphNodes(const bfs_t *b);

void freeBfs(bfs_t **b);

int *startBfs(bfs_t *b, int nodeId);

void addEdgeToNodes(bfs_t *b);

void nodesInit(bfs_t *b);

bfs_t *createBfs();

#endif

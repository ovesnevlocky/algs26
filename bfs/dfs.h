#ifndef DFS_H
#define DFS_H


#include "node.h"
#include "graph.h"

typedef struct
{
	graph_t *graph;
	node_t *nodes;
	int numNodes;
}dfs_t;

int *startDfs(dfs_t *d, int nodeId);

#endif

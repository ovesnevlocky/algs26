#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

void *myMalloc(size_t size)
{
	void *ret = calloc(size, 1);
	if(!ret)
	{
		printf("failed to allocate mme\n");
		exit(1);
	}

	return ret;
}

graph_t * allocateGraph(void)
{
	graph_t *g = myMalloc(sizeof(*g));
	g-> edges = NULL;
	g-> numEdges = 0;
	g-> capacity = MAX_SIZE;
	
	return g;
}

bfs_t *createBfs(void)
{
	bfs_t *ret = myMalloc(sizeof(*ret));
	ret -> graph = allocateGraph();
	ret -> nodes = NULL;
	ret -> numNodes = 0;
	return ret;
	
}

void freeGraph(bfs_t **g)
{
	free( (*g)-> graph-> edges);
	(*g)-> graph -> edges = NULL;
	
	free( (*g) -> graph);
	(*g) -> graph = NULL;

	free( (*g) -> nodes);
	(*g) -> nodes = NULL;

	return;	

}

graph_t* enlargeGraph(graph_t *g)
{

	int newSize = g-> capacity *2;
	edge_t *e = myMalloc(newSize * sizeof(edge_t));
	memcpy(e, g-> edges, g-> numEdges * sizeof(edge_t));
	g -> edges = e;
	g-> capacity = newSize;

	return g;
}

void printGraph(const graph_t *g)
{
	printf("digraph {\n");
	for(int i = 0; i < g-> numEdges; i++)
	{
		printf("%i -> %i;\n", g->edges[i].from, g->edges[i].to);
	}
	printf("}\n");

}


void nodesInit(bfs_t *b)
{
	b-> nodes = myMalloc(sizeof(node_t) * b-> numNodes);
	for(int i = 0; i < b-> numNodes; i++)
	{
		b-> nodes[i].edgeStart = -1;
		b-> nodes[i].edgeCount = 0;
		b-> nodes[i].isVisited = false;
	}	
}

void addEdgeToNodes(bfs_t *b)
{
	for(int i = 0; i < b-> graph->numEdges; i++)
	{
		int curr = b->graph->edges[i].from;
		if(b->nodes[curr].edgeStart == -1)
		{
			b->nodes[curr].edgeStart = i;
		}
		b->nodes[curr].edgeCount += 1;
	}
}

int loadGraph(graph_t *g,const char *fname)
{
	int numNodes = 0;
	edge_t e = {0};
	
	FILE *f = fopen(fname, "r");
	g-> edges = myMalloc(sizeof(edge_t) * MAX_SIZE);
	while(f)
	{
		if(g-> numEdges >= g -> capacity)
		{
			enlargeGraph(g);
		}
		int r = fscanf(f,"%i %i\n", &e.from, &e.to);
		if(r == 2)
		{
			g -> edges[g-> numEdges] = e;
			g-> numEdges += 1;
			if(e.from > numNodes || e.to > numNodes)
				numNodes = e.from > e.to ? e.from : e.to;
			
		}
		else
			break;
	}
	
	return numNodes += 1;

}





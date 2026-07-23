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


graph_t* enlargeGraph(graph_t *g)
{

	int newSize = g-> capacity *2;
	edge_t *e = myMalloc(newSize * sizeof(edge_t));
	memcpy(e, g-> edges, g-> numEdges * sizeof(edge_t));
	g -> edges = e;
	g-> capacity = newSize;

	return g;
}

void printEdge(int from, int to)
{
	printf("%i -- %i;\n", from, to);
}

void printGraph(const graph_t * g)
{
	int idxEdges = 0;
	int count = 0;

	printf("graph {\n");
	
	for(int i = 0; i  <g->numEdges ; i++)
	{
		edge_t e = g->edges[i];
		
		printEdge(e.from, e.to);	
	}
	
	printf("}\n");

}


int loadGraph(graph_t *g,const char *fname)
{

	int numNodes = 0;
	
	edge_t e = {0};
	edge_t e2 = {0};
	FILE *f = fopen(fname, "r");
	g-> edges = myMalloc(sizeof(edge_t) * MAX_SIZE);
	int from, to;
	while(f)
	{
		if(g-> numEdges >= g -> capacity)
		{
			enlargeGraph(g);
		}
		
		int r = fscanf(f,"%i %i\n", &from, &to);
		e.from = from;
		e.to = to;
		e2.from = to;
		e2.to = from;
		if(r == 2)
		{
			g -> edges[g-> numEdges] = e;
			g -> edges[g-> numEdges + 1] = e2;
			g-> numEdges += 1;
			g-> numEdges += 1;
			if(e.from > numNodes || e.to > numNodes)
				numNodes = e.from > e.to ? e.from : e.to;
			
		}
		else
			break;
	}
	
	if(f)
		fclose(f);	
	return numNodes += 1;

}

void printEdges(graph_t *g)
{
	for(int i = 0; i < g-> numEdges; i++)
		printf("%i -> %i\n", g->edges[i].from, 	g->edges[i].to);

}

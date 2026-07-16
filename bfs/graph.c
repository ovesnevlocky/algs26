#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "queue.h"

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

	free( *g);
	*g = NULL;

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


void printGraphNodes(const bfs_t *b)	
{
	int currNode = 0;
	graph_t *g = b->graph;
	printf("graph {\n");
	
	int *count = myMalloc(sizeof(int)* b->numNodes);

	for(int i = 0; i < b-> graph->numEdges; i++)
	{
		edge_t e = b->graph->edges[i];

		if(count[e.from] < b->nodes[e.from].edgeCount
		  &&  count[e.to] < b->nodes[e.to].edgeCount )
			
		{
			printEdge(g->edges[i].from, g->edges[i].to);
			
			count[e.from] += 1;			
			count[e.to] += 1;
		}

	}
	printf("}\n");
	
	free(count);
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
		edge_t e = b->graph->edges[i];
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

void printNodes(bfs_t *b)
{
	for(int i = 0; i < b->numNodes; i++)
	{
		printf("start: %i count: %i\n", b->nodes[i].edgeStart, b->nodes[i].edgeCount);
	}

}

void printEdges(graph_t *g)
{
	for(int i = 0; i < g-> numEdges; i++)
		printf("%i -> %i\n", g->edges[i].from, 	g->edges[i].to);

}

int *startBfs(bfs_t *b, int nodeId)
{
	int *ret = myMalloc(sizeof(int) * b->numNodes);
	int retIdx = 0;
	ret[retIdx++] = nodeId;
	int *count = myMalloc(sizeof(int) * b->numNodes);
	Queue q;
	queueInit(&q);

	pushQueue(&q, b->nodes[nodeId]);
	node_t curNode = b->nodes[nodeId];
	b->nodes[nodeId].isVisited = true;

	int idxInEdges = curNode.edgeStart;
	edge_t e;
	
	for(int i = 0; i < b->numNodes; i++)
	{
		
		curNode = popQueue(&q);
		edge_t e = b->graph->edges[curNode.edgeStart];
		nodeId = e.from;
		idxInEdges = curNode.edgeStart;	

		while(count[nodeId] < curNode.edgeCount)
		{
			e = b ->graph->edges[idxInEdges];
			if(b->nodes[e.to].isVisited == false) 
			{
				ret[retIdx++] = e.to;
				pushQueue(&q, b->nodes[e.to]);
				b->nodes[e.to].isVisited = true;
			}
			//push the visited node to the queue
			//get the next edge
			count[e.from] += 1;
			idxInEdges++;
		} 
	}	

	for(int i = 0; i < retIdx; i++)
		printf("%i ", ret[i]);

	putchar('\n');

	free(count);
	count = NULL;

	return ret;

}




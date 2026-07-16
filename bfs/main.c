#include <stdio.h>
#include "graph.h"
#include "radix.h"
#include "queue.h"
#include "bfs.h"

int main(int argc, char *argv[])
{

	char *fname = "graphs/big.txt";

	if(argc > 1)
		fname = argv[1];
	
	bfs_t *b = createBfs();
	b-> numNodes = loadGraph(b-> graph, fname);

	radixSort(b->graph->edges, b->graph->numEdges, b->numNodes);	

	nodesInit(b);

	addEdgeToNodes(b);
	
	//printGraphNodes(b);
	int *ret = startBfs(b, 0);
	if(ret != NULL)
	{
		for(int i = 0; i < b->numNodes; i++)
			printf("%i ", ret[i]);
		putchar('\n');
	}

	freeBfs(&b);
	if(ret)
		free(ret);

}

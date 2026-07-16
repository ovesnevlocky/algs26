#include <stdio.h>
#include "graph.h"
#include "radix.h"
#include "queue.h"

int main(int argc, char *argv[])
{

	char *fname = "graphs/g.txt";

	if(argc > 1)
	{
		fname = argv[1];
	}

	bfs_t *b = createBfs();
	b-> numNodes = loadGraph(b-> graph, fname);

	//printEdges(b->graph);

	
	radixSort(b->graph->edges, b->graph->numEdges, b->numNodes);	
	//puts("after sorting");
//	printEdges(b->graph);

	nodesInit(b);

	addEdgeToNodes(b);
	
//	printNodes(b);
//	printGraphNodes(b);
	int *ret = startBfs(b, 0);
	freeGraph(&b);
	free(ret);

}

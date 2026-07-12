#include <stdio.h>
#include "graph.h"


int main(int argc, char *argv[])
{

	char *fname = "g.txt";

	if(argc > 1)
	{
		fname = argv[1];
	}

	bfs_t *b = createBfs();
	b-> numNodes = loadGraph(b-> graph, fname);
	
	nodesInit(b);

	addEdgeToNodes(b);

	printGraph(b->graph);

	freeGraph(&b);

}

#include <stdio.h>
#include "radix.h"
#include "./bfs/bfs.h"
#include "./dfs/dfs.h"
#include <string.h>



int main(int argc, char *argv[])
{

	char *fname = "graphs/500.txt";

	if(argc > 1)
		fname = argv[1];
	
	bfs_t *b = createBfs();
	b-> numNodes = loadGraph(b-> graph, fname);

	radixSort(b->graph->edges, b->graph->numEdges, b->numNodes);	

	nodesInit(b);

	addEdgeToNodes(b);
	
	int *ret = NULL;	
	switch(argv[2][0])
	{
		case 'v':
		printGraphNodes(b);
		break;
		default:
		ret = startDfs((dfs_t*)b, 76);
		break;

	}
	
	if(ret != NULL)
	{
		for(int i = 0;i <  b->numNodes; i++)
			printf("%i\n", ret[i]);

		free(ret);
	}

	freeBfs(&b);

}

#include <stdio.h>
#include "radix.h"
#include "bfs.h"
#include "dfs.h"
#include <string.h>

int main(int argc, char *argv[])
{

	char *fname = "graphs/hard.txt";

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
		ret = startDfs((dfs_t*)b, 0);
		break;

	}
 
	if(ret != NULL)
	{
		for(int i = 0; ret[i] != -1; i++)
			printf("%i ", ret[i]);
		putchar('\n');

		free(ret);
	}

	freeBfs(&b);

}

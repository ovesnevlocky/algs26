#include <stdio.h>
#include "radix.h"
#include "./bfs/bfs.h"
#include "./dfs/dfs.h"
#include <string.h>
#include <stdbool.h>


bool isSorted(edge_t* edges, int numEdges)
{
	for(int i = 0; i < numEdges - 1; i++)
	{
		if(edges[i].from > edges[i + 1].from)
			return false;
	}
	printf("arr is sorted\n");
	return true;
}





int main(int argc, char *argv[])
{

	char *fname = "graphs/big.txt";

	if(argc > 1)
		fname = argv[1];
	
	bfs_t *b = createBfs();
	b-> numNodes = loadGraph(b-> graph, fname);
	
	if(isSorted(b->graph->edges, b->graph->numEdges) == false)
		radixSort(b->graph->edges, b->graph->numEdges, b->numNodes);	

	nodesInit(b);

	addEdgeToNodes(b);
	
	int *ret = NULL;
		
	switch(argv[2][0])
	{
		case 'v':
		printGraphNodes(b);
		break;
		case 'd':
		ret = startDfs((dfs_t*)b, 0);
		break;
		case 'b':
		ret = startBfs(b, 0);
		break;
		default:
		ret = startBfs(b, 0);
		break;

	}
	
	if(ret != NULL)
	{
	//	for(int i = 0;i <  b->numNodes; i++)
	//		printf("%i\n", ret[i]);

		free(ret);
	}

	freeBfs(&b);

}

#include "dfs.h"
#include "stack.h"
#include "stdlib.h"
#include "graph.h"


int *startDfs(dfs_t *d, int startNode)
{

	int *ret = myMalloc(sizeof(int) * (d->numNodes + 100));
	int retIdx = 0;
	ret[retIdx++] = startNode;
	int *count = myMalloc(sizeof(int) * d->numNodes);
	Stack s;
	stackInit(&s);
	
	stackPush(&s, d->nodes[startNode]);
	node_t curNode = d->nodes[startNode];
	d->nodes[startNode].isVisited = true;
	int idxInEdges = curNode.edgeStart;
	count[startNode] += 1;
	edge_t e;
	
	for(int i = 0; i < d -> numNodes; i++)
	{
		node_t peeked = stackPeek(&s);
		idxInEdges = peeked.edgeStart;	
		e = d->graph->edges[idxInEdges];
		while(peeked.edgeCount >1 )
		{
			
			e = d-> graph->edges[idxInEdges];

			if(d->nodes[e.to].isVisited == true 
			&& count[e.to] >= d-> nodes[e.to].edgeCount)
			{
				node_t n = stackPop(&s);
				break;
			}
			
			if(d->nodes[e.to].isVisited == true)
			{
				count[e.to] += 1;
				idxInEdges++;
				continue;
			}
			
			
			stackPush(&s, d->nodes[e.to]);
			ret[retIdx++] = e.to;
			d->nodes[e.to].isVisited = true;
			peeked = stackPeek(&s);		
			idxInEdges = peeked.edgeStart;	
			count[e.to] += 1;
	
		}
		
	}


		
	
	
	free(count);
	count = NULL;
	return ret; 

}

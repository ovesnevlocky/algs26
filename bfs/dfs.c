#include "dfs.h"
#include "stack.h"
#include "stdlib.h"
#include "graph.h"
#include <stdbool.h>

static int inicializeArr(int *a, int cap)
{
	for(int i = 0; i < cap + 30; i++)
		a[i] = -1;
	return 0;
}

static bool isExplored(int numEdges, int count)
{
	return count >= numEdges;

}


static bool isDegreeOne(int edgeCount)
{
	return edgeCount == 1;	
}

int *startDfs(dfs_t *d, int startNode)
{

	int *ret = myMalloc(sizeof(int) * (d->numNodes + 100));
	
	int retIdx = inicializeArr(ret, d->numNodes);
	ret[retIdx++] = startNode;	
	int *count = myMalloc(sizeof(int) * d->numNodes);
	Stack s;
	stackInit(&s);
	int idxInEdges;	
	edge_t e;
	node_t next;
	
	for(int i = 0; i < d -> numNodes; i++)
	{
		next = (i == 0) ? d->nodes[startNode] : stackPop(&s);
		idxInEdges = next.edgeStart;
		if(retIdx >= d->numNodes)
			break;
		while(retIdx < d->numNodes)
		{
			
			e = d-> graph->edges[idxInEdges];
			if(e.from != d->graph->edges[next.edgeStart].from)
				break;	
			if(d->nodes[e.to].isVisited == false)
			{
				if(d->nodes[e.from].isVisited == false 
				&& d->nodes[e.to].edgeCount > 1)
				{
					stackPush(&s, d->nodes[e.from]);
				}
				else if(isDegreeOne(d->nodes[e.to].edgeCount))
				{
					//meaning has no node after this e.to(list in a tree)
					//these nodes dont have to be pushed to the stack
					ret[retIdx++] = e.to;
					idxInEdges++;
					count[e.from] += 1;
					d->nodes[e.to].isVisited = true;
					continue;
				}	
				next = d->nodes[e.to];
				ret[retIdx++] = e.to;
				d->nodes[e.from].isVisited = true;
				count[e.from] += 1;
				idxInEdges = next.edgeStart;
			}
			else if(d->nodes[e.to].isVisited == true)
			{
				idxInEdges++;
				//count[e.from] += 1;
				if(e.from != d->graph->edges[idxInEdges].from)
				{
					if(d->nodes[e.from].isVisited == false)
					{
						d->nodes[e.from].isVisited = true;
					}
					break;
				}

			}
			//if we check all edges of this node
			if(count[e.from] >= d->nodes[e.from].edgeCount
			|| retIdx >= d->numNodes) 
			{
				break;
			}
		}
	}
	free(count);
	count = NULL;
	return ret; 
}

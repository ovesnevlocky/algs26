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
	int *count = myMalloc(sizeof(int) * d->numNodes);
	Stack s;
	stackInit(&s);

	stackPush(&s, d->nodes[startNode]);
	//count[startNode] += 1;		
	ret[retIdx++] = startNode;	
	d->nodes[startNode].isVisited = true;

	int idxInEdges;	
	edge_t e;
	node_t next;
	int offset = 0;	
	while(retIdx < d->numNodes)	
	{
		node_t peeked = stackPeek(&s);
		if(count[peeked.nodeId] >= peeked.edgeCount)
		{
			next = stackPop(&s);
			if(next.isVisited == true)
				continue;
		}
		else
			next = peeked;

		offset = count[ next.nodeId ];

		while(count[next.nodeId] < next.edgeCount)
		{
			e = d-> graph->edges[ next.edgeStart + offset ];

			if(d->nodes[e.to].isVisited == false)
			{
				//want to push to the stack if not visited yet
				if(d->nodes[e.from].isVisited == false 
				&& d->nodes[e.to].edgeCount > 1)
				{
					stackPush(&s, d->nodes[e.from]);
					d->nodes[e.from].isVisited = true;
				}
				else if(isDegreeOne(d->nodes[e.to].edgeCount))
				{
					//meaning has no node after this e.to(list in a tree)
					//these nodes dont have to be pushed to the stack
					ret[retIdx++] = e.to;
					count[e.from] += 1;
					offset = count[e.from];
					d->nodes[e.to].isVisited = true;
					continue;
				}
				//visit the next node	
				next = d->nodes[e.to];
				ret[retIdx++] = e.to;
				count[e.from] += 1;
				offset = count[e.to];
			}
			else if(d->nodes[e.to].isVisited == true)
			{
				count[e.from] += 1;
				offset = count[e.from];
			}
		}
		if(retIdx >= d->numNodes)
			break;
		if(count[next.nodeId] >= next.edgeCount)
			d->nodes[next.nodeId].isVisited = true;
	}
	free(count);
	count = NULL;
	return ret; 
}

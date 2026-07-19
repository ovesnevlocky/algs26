#include "queue.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

bfs_t *createBfs(void)
{
        bfs_t *ret = myMalloc(sizeof(*ret));
        ret -> graph = allocateGraph();
        ret -> nodes = NULL;
        ret -> numNodes = 0;
        return ret;

}

void freeBfs(bfs_t **g)
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

void static printEdge(int from, int to)
{
	printf("%i -- %i;\n", from, to);
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
                        printEdge(g->edges[i].from, g->edges[i].to    );
			
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
	int nodeId = 0;	
        for(int i = 0; i < b-> graph->numEdges; i++)
        {
                int curr = b->graph->edges[i].from;
                edge_t e = b->graph->edges[i];
                if(b->nodes[curr].edgeStart == -1)
                {
                        b->nodes[curr].edgeStart = i;
			b->nodes[curr].nodeId = nodeId;
			nodeId++;
                }
                b->nodes[curr].edgeCount += 1;
        }
}


void printNodes(bfs_t *b)
{
	
        for(int i = 0; i < b->numNodes; i++)
        {
                printf("start: %i count: %i\n", b->nodes[i].edgeStart, b->nodes[i].edgeCount);
        }

}

int *startBfs(bfs_t *b, int nodeId)
{
	if(nodeId > b->numNodes)
	{
		printf("biggest possible node to start is %i, got %i\n", b->numNodes, nodeId);
		return NULL;
	}
	
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


         free(count);
         count = NULL;

         return ret;

}




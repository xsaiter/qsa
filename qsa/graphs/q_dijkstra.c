#include "q_dijkstra.h"

#include "../q_queue.h"

q_graph_shortest_paths *q_dijkstra(const q_graph *g, int s)
{
    q_graph_shortest_paths *res;
    res = xmalloc(sizeof(q_graph_shortest_paths));
    
    res->dist = xmalloc0(g->nv * sizeof(int));
    
    for(int i = 0; i< g->nv; ++i){
        res->dist[i] = -1;
    }
    
    
    
    return res;
}
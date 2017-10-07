#include <stdio.h>

#include "q_dijkstra.h"

#include "../q_utils.h"
#include "../q_heap.h"

void q_dijkstra(const q_graph *g, int s, q_graph_shortest_paths *res)
{
    res->s = s;
    res->dist = xmalloc0(g->nv * sizeof (double));
    for (int i = 0; i < g->nv; ++i) {
        res->dist[i] = -1;
    }    

    q_heap *h = q_heap_new(g->nv, sizeof (int), &q_compare_int);
    
    q_heap_add(h, &s);

    while (!q_heap_empty(h)) {
        int t = Q_VPTR_TO_INT(q_heap_extract(h));

        q_graph_edge *e = g->adj[t];

        while (e) {
            double d = res->dist[e->b] + e->weight;
            if (res->dist[e->b] == -1.0 || d < res->dist[e->b]) {
                q_heap_add(h, &(e->b));
                res->dist[e->b] = d;
            }
            e = e->next;
        }
    }

    q_heap_free(h);    
}
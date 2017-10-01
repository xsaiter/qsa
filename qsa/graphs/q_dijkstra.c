#include "q_dijkstra.h"

#include "../q_pqueue.h"
#include "../q_utils.h"

q_graph_shortest_paths *q_dijkstra(const q_graph *g, int s)
{
    q_graph_shortest_paths *res;
    
    res = xmalloc(sizeof (q_graph_shortest_paths));
    res->s = s;
    res->dist = xmalloc0(g->nv * sizeof (double));
    for (int i = 0; i < g->nv; ++i) {
        res->dist[i] = -1;
    }    

    q_pqueue *q = q_pqueue_new(g->nv, sizeof (int), &q_compare_int);
    q_pqueue_insert(q, &s);

    while (!q_pqueue_empty(q)) {
        int t = Q_VPTR_TO_INT(q_pqueue_extract(q));

        q_graph_edge *e = g->adj[t];

        while (e) {
            double d = res->dist[e->b] + e->weight;
            if (res->dist[e->b] == -1.0 || d < res->dist[e->b]) {
                q_pqueue_insert(q, &(e->b));
                res->dist[e->b] = d;
            }
            e = e->next;
        }
    }

    q_pqueue_free(q);

    return res;
}
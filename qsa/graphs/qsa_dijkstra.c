#include <stdio.h>

#include "qsa_dijkstra.h"

#include "../qsa_heap.h"

void qsa_dijkstra(const struct qsa_graph *g, int s,
                  struct qsa_graph_shortest_paths *res) {
  res->s = s;
  res->dist = qsa_malloc0(g->nv * sizeof(double));
  for (int i = 0; i < g->nv; ++i) {
    res->dist[i] = -1;
  }

  struct qsa_heap *h = qsa_heap_create(g->nv, sizeof(int), &qsa_cmp_int);

  qsa_heap_add(h, &s);

  while (!qsa_heap_empty(h)) {
    int t = QSA_VPTR_TO_INT(qsa_heap_top(h));
    qsa_heap_pop(h);

    struct qsa_graph_edge *e = g->adj[t];

    while (e) {
      double d = res->dist[e->b] + e->weight;
      if (res->dist[e->b] == -1.0 || d < res->dist[e->b]) {
        qsa_heap_add(h, &(e->b));
        res->dist[e->b] = d;
      }
      e = e->next;
    }
  }

  qsa_heap_free(h);
}

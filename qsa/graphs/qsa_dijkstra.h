#ifndef QSA_DIJKSTRA_H
#define QSA_DIJKSTRA_H

#include "qsa_graph.h"

void qsa_dijkstra(const struct qsa_graph *g, int s,
                  struct qsa_graph_shortest_paths *res);

#endif /* QSA_DIJKSTRA_H */

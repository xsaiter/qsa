#ifndef Q_DIJKSTRA_H
#define Q_DIJKSTRA_H

#include "qsa_graph.h"

#ifdef __cplusplus
extern "C" {
#endif    

    void q_dijkstra(const q_graph *g, int s, q_graph_shortest_paths *res);

#ifdef __cplusplus
}
#endif

#endif /* Q_DIJKSTRA_H */
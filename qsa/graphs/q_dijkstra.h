#ifndef Q_DIJKSTRA_H
#define Q_DIJKSTRA_H

#include "q_graph.h"

#ifdef __cplusplus
extern "C" {
#endif    

    q_graph_shortest_paths *q_dijkstra(const q_graph *g, int s);

#ifdef __cplusplus
}
#endif

#endif /* Q_DIJKSTRA_H */
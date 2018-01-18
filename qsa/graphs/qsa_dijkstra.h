#ifndef _QSA_DIJKSTRA_H
#define _QSA_DIJKSTRA_H

#include "qsa_graph.h"

#ifdef __cplusplus
extern "C" {
#endif    

    void q_dijkstra(const q_graph *g, int s, q_graph_shortest_paths *res);

#ifdef __cplusplus
}
#endif

#endif /* _QSA_DIJKSTRA_H */
#ifndef QSA_DIJKSTRA_H
#define QSA_DIJKSTRA_H

#include "qsa_graph.h"

#ifdef __cplusplus
extern "C" {
#endif    

    void qsa_dijkstra(const qsa_graph_s *g, int s, qsa_graph_shortest_paths_s *res);

#ifdef __cplusplus
}
#endif

#endif /* QSA_DIJKSTRA_H */
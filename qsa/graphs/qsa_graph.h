#ifndef QSA_GRAPH_H
#define QSA_GRAPH_H

#include <stdbool.h>

typedef struct qsa_graph_edge_s {
    int b;
    double weight;
    struct qsa_graph_edge_s *next;
} qsa_graph_edge_s;

typedef struct {
    qsa_graph_edge_s **adj; // adjacency list
    int nv; // number of vertices
    int ne; // number of edges
    bool directed;
    bool weighed;
} qsa_graph_s;

typedef void (*qsa_visit_fn)(qsa_graph_s *g, qsa_graph_edge_s *e, void *arg);

bool *qsa_graph_marked_alloc(const qsa_graph_s *g);

qsa_graph_s *qsa_graph_create(int nv, bool directed, bool weighed);

void qsa_graph_free(qsa_graph_s *g);

void qsa_graph_add_edge(qsa_graph_s *g, int a, int b, double weight);

void qsa_graph_print(qsa_graph_s *g);

void qsa_graph_traversal_bfs(qsa_graph_s *g, int s, qsa_visit_fn visit, void *arg);

void qsa_graph_traversal_dfs(qsa_graph_s *g, int s, qsa_visit_fn visit, void *arg);

typedef struct {
    int nv; // number of vertices
    int s; // source vertex
    bool *marked; // marked[i] - exists paths from s to i
    int *dist; // dist[i] - distance from s to i
} qsa_graph_paths_s;

qsa_graph_paths_s *qsa_graph_paths_new(qsa_graph_s *g, int s);

void qsa_graph_paths_free(qsa_graph_paths_s *paths);

void qsa_graph_paths_bfs(qsa_graph_s *g, qsa_graph_paths_s *paths);

void qsa_graph_paths_dfs(qsa_graph_s *g, qsa_graph_paths_s *paths);

typedef struct {
    int nv; // number of vertices
    int s; // source vertex
    double *dist; // dist[i] - distance from s to i
    qsa_graph_edge_s *edges;
} qsa_graph_shortest_paths_s;

bool qsa_graph_shortest_paths_to(qsa_graph_shortest_paths_s *paths, int v);

double qsa_graph_shortest_paths_distance_to(qsa_graph_shortest_paths_s *paths, int v);

#endif /* QSA_GRAPH_H */

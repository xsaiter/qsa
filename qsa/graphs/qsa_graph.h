#ifndef QSA_GRAPH_H
#define QSA_GRAPH_H

#include <stdbool.h>

struct qsa_graph_edge {
  int b;
  double weight;
  struct qsa_graph_edge *next;
};

struct qsa_graph {
  struct qsa_graph_edge **adj; // adjacency list
  int nv;                      // number of vertices
  int ne;                      // number of edges
  bool directed;
  bool weighed;
};

typedef void (*qsa_visit_fn)(struct qsa_graph *g, struct qsa_graph_edge *e,
                             void *arg);

bool *qsa_graph_marked_alloc(const struct qsa_graph *g);

struct qsa_graph *qsa_graph_create(int nv, bool directed, bool weighed);

void qsa_graph_free(struct qsa_graph *g);

void qsa_graph_add_edge(struct qsa_graph *g, int a, int b, double weight);

void qsa_graph_print(struct qsa_graph *g);

void qsa_graph_traversal_bfs(struct qsa_graph *g, int s, qsa_visit_fn visit,
                             void *arg);

void qsa_graph_traversal_dfs(struct qsa_graph *g, int s, qsa_visit_fn visit,
                             void *arg);

struct qsa_graph_paths {
  int nv;       // number of vertices
  int s;        // source vertex
  bool *marked; // marked[i] - exists paths from s to i
  int *dist;    // dist[i] - distance from s to i
};

struct qsa_graph_paths *qsa_graph_paths_new(struct qsa_graph *g, int s);

void qsa_graph_paths_free(struct qsa_graph_paths *paths);

void qsa_graph_paths_bfs(struct qsa_graph *g, struct qsa_graph_paths *paths);

void qsa_graph_paths_dfs(struct qsa_graph *g, struct qsa_graph_paths *paths);

struct qsa_graph_shortest_paths {
  int nv;       // number of vertices
  int s;        // source vertex
  double *dist; // dist[i] - distance from s to i
  struct qsa_graph_edge *edges;
};

bool qsa_graph_shortest_paths_to(struct qsa_graph_shortest_paths *paths, int v);

double
qsa_graph_shortest_paths_distance_to(struct qsa_graph_shortest_paths *paths,
                                     int v);

#endif /* QSA_GRAPH_H */

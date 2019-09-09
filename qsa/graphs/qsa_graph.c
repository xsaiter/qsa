#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../qsa_queue.h"
#include "../qsa_utils.h"

#include "qsa_graph.h"

struct qsa_graph *qsa_graph_create(int nv, bool directed, bool weighed) {
  struct qsa_graph *g = qsa_malloc(sizeof(struct qsa_graph));
  g->nv = nv;
  g->adj = qsa_calloc(g->nv, sizeof(struct qsa_graph_edge *));
  g->directed = directed;
  g->weighed = weighed;
  return g;
}

void qsa_graph_free(struct qsa_graph *g) {
  for (int i = 0; i < g->nv; ++i) {
    struct qsa_graph_edge *e = g->adj[i];
    while (e) {
      free(e);
      e = e->next;
    }
  }
  free(g->adj);
  free(g);
}

static void add_edge(struct qsa_graph *g, int a, int b, double weight) {
  struct qsa_graph_edge *e = qsa_malloc(sizeof(struct qsa_graph_edge));
  e->b = b;
  e->weight = weight;
  e->next = g->adj[a];
  g->adj[a] = e;
}

void qsa_graph_add_edge(struct qsa_graph *g, int a, int b, double weight) {
  add_edge(g, a, b, weight);
  if (!g->directed) {
    add_edge(g, b, a, weight);
  }
  g->ne++;
}

void qsa_graph_print(struct qsa_graph *g) {
  for (int i = 0; i < g->nv; ++i) {
    printf("%d", i);

    struct qsa_graph_edge *e = g->adj[i];

    while (e) {
      printf("->%d", e->b);
      e = e->next;
    }

    printf("\n");
  }
}

inline bool *qsa_graph_marked_alloc(const struct qsa_graph *g) {
  return calloc(g->nv, sizeof(bool));
}

void qsa_graph_traversal_bfs(struct qsa_graph *g, int s, qsa_visit_fn visit,
                             void *arg) {
  bool *marked = qsa_graph_marked_alloc(g);

  struct qsa_queue *q = qsa_queue_create_int();
  qsa_queue_enq(q, &s);

  while (!qsa_queue_empty(q)) {
    int i = QSA_VPTR_TO_INT(qsa_queue_deq(q));

    struct qsa_graph_edge *e = g->adj[i];

    while (e) {
      if (!marked[e->b]) {
        visit(g, e, arg);
        qsa_queue_enq(q, &(e->b));
      }
      e = e->next;
    }

    marked[i] = true;
  }

  qsa_queue_free(q);

  free(marked);
}

static void dfs(struct qsa_graph *g, int i, bool *marked, qsa_visit_fn visit,
                void *arg) {
  marked[i] = true;

  struct qsa_graph_edge *e = g->adj[i];

  while (e) {
    if (!marked[e->b]) {
      visit(g, e, arg);
      dfs(g, e->b, marked, visit, arg);
    }
    e = e->next;
  }
}

void qsa_graph_traversal_dfs(struct qsa_graph *g, int s, qsa_visit_fn visit,
                             void *arg) {
  bool *marked = qsa_graph_marked_alloc(g);
  dfs(g, s, marked, visit, arg);
  free(marked);
}

struct qsa_graph_paths *qsa_graph_paths_new(struct qsa_graph *g, int s) {
  struct qsa_graph_paths *paths = qsa_malloc(sizeof(struct qsa_graph_paths));

  paths->marked = qsa_graph_marked_alloc(g);
  paths->dist = qsa_malloc0(g->nv);
  paths->s = s;
  paths->nv = g->nv;

  return paths;
}

void qsa_graph_paths_free(struct qsa_graph_paths *paths) {
  free(paths->dist);
  free(paths->marked);
  free(paths);
}

void qsa_graph_paths_bfs(struct qsa_graph *g, struct qsa_graph_paths *paths) {
  struct qsa_queue *q = qsa_queue_create_int();
  qsa_queue_enq(q, &(paths->s));

  while (!qsa_queue_empty(q)) {
    int i = QSA_VPTR_TO_INT(qsa_queue_deq(q));

    struct qsa_graph_edge *e = g->adj[i];

    while (e) {
      if (!paths->marked[e->b]) {
        qsa_queue_enq(q, &(e->b));
        paths->dist[e->b] = paths->dist[i] + 1;
      }
      e = e->next;
    }

    paths->marked[i] = true;
  }

  qsa_queue_free(q);
}

static void paths_dfs(struct qsa_graph *g, struct qsa_graph_paths *paths,
                      int i) {
  paths->marked[i] = true;
  struct qsa_graph_edge *e = g->adj[i];

  while (e) {
    if (!paths->marked[e->b]) {
      paths->dist[e->b] = paths->dist[i] + 1;
      paths_dfs(g, paths, e->b);
    }
    e = e->next;
  }
}

void qsa_graph_paths_dfs(struct qsa_graph *g, struct qsa_graph_paths *paths) {
  paths_dfs(g, paths, paths->s);
}

bool qsa_graph_shortest_paths_to(struct qsa_graph_shortest_paths *paths,
                                 int v) {
  return paths->dist[v] != -1.0;
}

double
qsa_graph_shortest_paths_distance_to(struct qsa_graph_shortest_paths *paths,
                                     int v) {
  return paths->dist[v];
}

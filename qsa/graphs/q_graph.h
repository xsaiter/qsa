#ifndef Q_GRAPH_H
#define Q_GRAPH_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_graph_edge {
        int b;
        double weight;
        struct q_graph_edge *next;
    } q_graph_edge;

    typedef struct {
        q_graph_edge **adj; // adjacency list
        int nv; // number of vertices
        int ne; // number of edges
        bool directed;
        bool weighed;
    } q_graph;

    typedef void (*visit_fn)(q_graph *g, q_graph_edge *e, void *arg);

    void q_graph_init(q_graph *g, int nv, bool directed, bool weighed);
    void q_graph_destroy(q_graph *g);
    void q_graph_add_edge(q_graph *g, int a, int b, double weight);
    void q_graph_print(q_graph *g);
    void q_graph_bfs(q_graph *g, int s, visit_fn visit, void *arg);
    void q_graph_dfs(q_graph *g, int s, visit_fn visit, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* Q_GRAPH_H */

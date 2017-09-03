#ifndef Q_GRAPH_H
#define Q_GRAPH_H

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_graph_node {
        int sink;
        int weight;
        struct q_graph_node *next;
    } q_graph_node;

    typedef struct {
        q_graph_node **nodes;
        int nodes_count;
        int edges_count;
        bool directed;
    } q_graph;

    void q_graph_init(q_graph *g, int nv);
    void q_graph_free(q_graph *g);
    void q_graph_add_node(q_graph *g, int node);
    void q_graph_add_edge(q_graph *g, int src, int dest, int w);

#ifdef __cplusplus
}
#endif

#endif /* Q_GRAPH_H */

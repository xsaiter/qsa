#ifndef Q_GRAPH_H
#define Q_GRAPH_H

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_graph_node {
        int b;
        double weight;
        struct q_graph_node *next;
    } q_graph_node;

    typedef struct {
        q_graph_node **adj;
        int nnodes;
        int nedges;
        bool directed;
        bool weighed;
    } q_graph;

    void q_graph_init(q_graph *g, int nnodes, bool directed, bool weighed);
    void q_graph_free(q_graph *g);    
    void q_graph_add_edge(q_graph *g, int a, int b, double weight);
    void q_graph_print(q_graph *g);

#ifdef __cplusplus
}
#endif

#endif /* Q_GRAPH_H */

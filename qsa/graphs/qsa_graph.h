#ifndef _QSA_GRAPH_H
#define _QSA_GRAPH_H

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

    bool *q_graph_marked_alloc(const q_graph *g);

    q_graph *q_graph_new(int nv, bool directed, bool weighed);
    void q_graph_free(q_graph *g);
    void q_graph_add_edge(q_graph *g, int a, int b, double weight);
    void q_graph_print(q_graph *g);

    void q_graph_traversal_bfs(q_graph *g, int s, visit_fn visit, void *arg);
    void q_graph_traversal_dfs(q_graph *g, int s, visit_fn visit, void *arg);

    typedef struct {
        int nv; // number of vertices
        int s; // source vertex
        bool *marked; // marked[i] - exists paths from s to i
        int *dist; // dist[i] - distance from s to i
    } q_graph_paths;

    q_graph_paths *q_graph_paths_new(q_graph *g, int s);
    void q_graph_paths_free(q_graph_paths *paths);
    
    void q_graph_paths_bfs(q_graph *g, q_graph_paths *paths);
    void q_graph_paths_dfs(q_graph *g, q_graph_paths *paths);
    
    typedef struct {
        int nv; // number of vertices
        int s; // source vertex
        double *dist; // dist[i] - distance from s to i
        q_graph_edge *edges;
    } q_graph_shortest_paths;
        
    bool q_graph_shortest_paths_to(q_graph_shortest_paths *paths, int v);
    double q_graph_shortest_paths_distance_to(q_graph_shortest_paths *paths, int v);

#ifdef __cplusplus
}
#endif

#endif /* _QSA_GRAPH_H */

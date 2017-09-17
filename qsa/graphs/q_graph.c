#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../q_utils.h"
#include "../q_queue.h"

#include "q_graph.h"

q_graph *q_graph_new(int nv, bool directed, bool weighed)
{
    q_graph *g = xmalloc(sizeof(q_graph));    
    
    g->nv = nv;
    g->adj = xcalloc(g->nv, sizeof (q_graph_edge*));
    g->directed = directed;
    g->weighed = weighed;
    
    return g;
}

void q_graph_free(q_graph *g)
{
    for (int i = 0; i < g->nv; ++i) {
        q_graph_edge *e = g->adj[i];
        while (e) {
            free(e);
            e = e->next;
        }
    }
    free(g->adj);
    free(g);
}

static void add_edge(q_graph *g, int a, int b, double weight)
{
    q_graph_edge *e = xmalloc(sizeof (q_graph_edge));
    e->b = b;
    e->weight = weight;
    e->next = g->adj[a];
    g->adj[a] = e;
}

void q_graph_add_edge(q_graph *g, int a, int b, double weight)
{
    add_edge(g, a, b, weight);
    if (!g->directed) {
        add_edge(g, b, a, weight);
    }
    g->ne++;
}

void q_graph_print(q_graph *g)
{
    for (int i = 0; i < g->nv; ++i) {
        printf("%d", i);

        q_graph_edge *e = g->adj[i];

        while (e) {
            printf("->%d", e->b);
            e = e->next;
        }

        printf("\n");
    }
}

inline bool *q_graph_marked_alloc(const q_graph *g)
{
    return calloc(g->nv, sizeof (bool));
}

void q_graph_bfs(q_graph *g, int s, visit_fn visit, void *arg)
{
    bool *marked = q_graph_marked_alloc(g);
    
    q_queue *q = q_queue_new_int();
    q_queue_enq(q, &s);    

    while (!q_queue_empty(q)) {
        int i = Q_VPTR_TO_INT(q_queue_deq(q));

        q_graph_edge *e = g->adj[i];

        while (e) {
            if (!marked[e->b]) {
                visit(g, e, arg);
                q_queue_enq(q, &(e->b));
            }
            e = e->next;
        }

        marked[i] = true;
    }
    
    q_queue_free(q);
    
    free(marked);
}

static void dfs(q_graph *g, int i, bool *marked, visit_fn visit, void *arg)
{
    marked[i] = true;

    q_graph_edge *e = g->adj[i];

    while (e) {
        if (!marked[e->b]) {
            visit(g, e, arg);
            dfs(g, e->b, marked, visit, arg);
        }
        e = e->next;
    }
}

void q_graph_dfs(q_graph *g, int s, visit_fn visit, void *arg)
{
    bool *marked = q_graph_marked_alloc(g);
    dfs(g, s, marked, visit, arg);
    free(marked);
}

q_graph_paths *q_graph_paths_new(q_graph *g, int s)
{
    q_graph_paths *paths = xmalloc(sizeof(q_graph_paths));
    
    paths->marked = q_graph_marked_alloc(g);
    paths->distance = xmalloc0(g->nv);
    paths->s = s;
    paths->nv = g->nv;    
    
    return paths;
}

void q_graph_paths_free(q_graph_paths *paths)
{
    free(paths->distance);
    free(paths->marked);
    free(paths);
}

void q_graph_bfs_paths(q_graph *g, q_graph_paths *paths)
{        
    q_queue *q = q_queue_new_int();
    q_queue_enq(q, &(paths->s));

    while (!q_queue_empty(q)) {
        int i = Q_VPTR_TO_INT(q_queue_deq(q));

        q_graph_edge *e = g->adj[i];

        while (e) {
            if (!paths->marked[e->b]) {                
                q_queue_enq(q, &(e->b));
                paths->distance[e->b] = paths->distance[i] + 1;
            }
            e = e->next;
        }

        paths->marked[i] = true;
    }
    
    q_queue_free(q);
}

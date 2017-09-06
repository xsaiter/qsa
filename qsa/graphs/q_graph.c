#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../q_utils.h"
#include "../q_queue.h"

#include "q_graph.h"

void q_graph_init(q_graph *g, int nv, bool directed, bool weighed)
{
    g->nv = nv;
    g->adj = calloc(g->nv, sizeof (q_graph_edge*));
    g->directed = directed;
    g->weighed = weighed;
}

void q_graph_destroy(q_graph *g)
{
    for (int i = 0; i < g->nv; ++i) {
        q_graph_edge *e = g->adj[i];
        while (e) {
            free(e);
            e = e->next;
        }
    }
    free(g->adj);
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

static inline bool *q_graph_marked_alloc(const q_graph *g)
{
    return calloc(g->nv, sizeof (bool));
}

void q_graph_bfs(q_graph *g, int s, visit_fn visit, void *arg)
{
    bool *marked = q_graph_marked_alloc(g);
    
    q_queue q;
    q_queue_init(&q);
    q_queue_enq(&q, Q_INT_TO_VOIDPTR(s));    

    while (!q_queue_empty(&q)) {
        int i = Q_VOIDPTR_TO_INT(q_queue_deq(&q));

        q_graph_edge *e = g->adj[i];

        while (e) {
            if (!marked[e->b]) {
                visit(g, e, arg);
                q_queue_enq(&q, Q_INT_TO_VOIDPTR(e->b));
            }
            e = e->next;
        }

        marked[i] = true;
    }
    
    q_queue_destroy(&q);
    
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
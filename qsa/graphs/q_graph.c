#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "q_graph.h"

void q_graph_init(q_graph *g, int nnodes, bool directed, bool weighed)
{
    g->nnodes = nnodes;

    size_t adj_size = g->nnodes * sizeof (q_graph_node*);

    g->adj = malloc(adj_size);
    memset(g->adj, 0, adj_size);

    g->directed = directed;
    g->weighed = weighed;
}

void q_graph_free(q_graph *g)
{
    free(g->adj);
}

static void add_edge(q_graph *g, int a, int b, double weight)
{
    q_graph_node *node = malloc(sizeof (q_graph_node));
    if (!node) {
        perror("node");
        exit(EXIT_FAILURE);
    }

    node->b = b;
    node->weight = weight;
    
    node->next = g->adj[a];        
    g->adj[a] = node;
}

void q_graph_add_edge(q_graph *g, int a, int b, double weight)
{
    add_edge(g, a, b, weight);
    if (!g->directed) {
        add_edge(g, b, a, weight);
    }
    g->nedges++;
}

void q_graph_print(q_graph *g)
{
    for (int i = 0; i < g->nnodes; ++i) {
        printf("%d", i);
        
        q_graph_node *cur = g->adj[i];
        
        while (cur) {
            printf("->%d", cur->b);
            cur = cur->next;
        }
        
        printf("\n");
    }
} 
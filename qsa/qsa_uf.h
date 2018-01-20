/*
 * union-find data structure (disjoint sets)
 */

#ifndef QSA_UF_H
#define QSA_UF_H

typedef struct q_uf_node {
    struct q_uf_node *parent;
    int rank;
    void *value;
} q_uf_node;

typedef struct {
    q_uf_node *nodes;
    int nnodes;
    size_t value_size;
} q_uf;

#endif /* QSA_UF_H */
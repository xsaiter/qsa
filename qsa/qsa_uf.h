/*
 * union-find data structure (disjoint sets)
 */

#ifndef QSA_UF_H
#define QSA_UF_H

#include <stddef.h>

typedef struct q_uf_node_s {
    struct q_uf_node_s *parent;
    int rank;
    void *value;
} q_uf_node_s;

typedef struct {
    q_uf_node_s *nodes;
    int nnodes;
    size_t value_size;
} q_uf_s;

#endif /* QSA_UF_H */
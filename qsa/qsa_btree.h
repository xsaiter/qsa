/*
 * btree
 */

#ifndef QSA_BTREE_H
#define QSA_BTREE_H

#include "qsa_core.h"

typedef struct qsa_btree_node_s {
    void *data;
    bool is_leaf;
    size_t nkeys;
    void ** keys;
    struct qsa_btree_node_s *parent;
    struct qsa_btree_node_s *children;    
} qsa_btree_node_s;

typedef struct {
    size_t data_size;
    size_t key_size;
    qsa_compare_fn *cmp_keys;
    qsa_btree_node_s *root;
    size_t min_degree;    
} qsa_btree_s;

qsa_btree_s *qsa_btree_new(size_t min_degree, size_t key_size, qsa_compare_fn *cmp_keys);


#endif /* QSA_BTREE_H */
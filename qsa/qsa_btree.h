/*
 * btree
 */

#ifndef QSA_BTREE_H
#define QSA_BTREE_H

#include "qsa_core.h"

typedef struct {
    int key;
    int ptr;
} qsa_btree_entry_s;

typedef struct qsa_btree_node_s {
    bool is_leaf;
    size_t n;
    qsa_btree_entry_s *e;
    struct qsa_btree_node_s *c;    
} qsa_btree_node_s;

typedef struct {
    qsa_btree_node_s *root;
    size_t degree;
    size_t max_ne;
    size_t max_nc;
} qsa_btree_s;

qsa_btree_s *qsa_btree_create(size_t degree);

void qsa_btree_insert(qsa_btree_s *t, int key, int ptr);


#endif /* QSA_BTREE_H */
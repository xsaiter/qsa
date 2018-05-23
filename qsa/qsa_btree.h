/*
 * btree
 */

#ifndef QSA_BTREE_H
#define QSA_BTREE_H

#include "qsa_core.h"

typedef struct {
    int key;
    int ptr;
} qsa_btree_cell_s;

typedef struct qsa_btree_node_s {
    bool is_leaf;
    size_t ncells;
    qsa_btree_cell_s *cells;
    struct qsa_btree_node_s *children;
    struct qsa_btree_node_s *parent;
} qsa_btree_node_s;

typedef struct {
    qsa_btree_node_s *root;
    size_t degree;
    size_t nce; // max cells
    size_t nch; // max children
} qsa_btree_s;

qsa_btree_s *qsa_btree_create(size_t degree);

void qsa_btree_insert(qsa_btree_s *t, int key, int ptr);


#endif /* QSA_BTREE_H */
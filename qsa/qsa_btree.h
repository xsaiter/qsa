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
  size_t n;                    // count entries
  qsa_btree_entry_s **e;       // entries
  struct qsa_btree_node_s **c; // children
} qsa_btree_node_s;

typedef struct {
  qsa_btree_node_s *root;
  size_t degree;
  size_t max_ne; // max entries
  size_t max_nc; // max children
} qsa_btree_s;

qsa_btree_s *qsa_btree_create(size_t degree);

void qsa_btree_free(qsa_btree_s *t);

void qsa_btree_insert(qsa_btree_s *t, int key, int ptr);

#endif /* QSA_BTREE_H */

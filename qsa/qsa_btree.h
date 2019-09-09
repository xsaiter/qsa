/*
 * btree
 */

#ifndef QSA_BTREE_H
#define QSA_BTREE_H

#include "qsa_core.h"

struct qsa_btree_entry {
  int key;
  int ptr;
};

struct qsa_btree_node {
  bool is_leaf;
  size_t n;                   // count entries
  struct qsa_btree_entry **e; // entries
  struct qsa_btree_node **c;  // children
};

struct qsa_btree {
  struct qsa_btree_node *root;
  size_t degree;
  size_t max_ne; // max entries
  size_t max_nc; // max children
};

struct qsa_btree *qsa_btree_create(size_t degree);

void qsa_btree_free(struct qsa_btree *t);

void qsa_btree_insert(struct qsa_btree *t, int key, int ptr);

#endif /* QSA_BTREE_H */

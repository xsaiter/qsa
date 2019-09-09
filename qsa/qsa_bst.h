/*
 * binary search tree
 */

#ifndef QSA_BST_H
#define QSA_BST_H

#include "qsa_core.h"

struct qsa_bst_node {
  void *key;
  struct qsa_bst_node *parent;
  struct qsa_bst_node *left;
  struct qsa_bst_node *right;
};

struct qsa_bst {
  struct qsa_bst_node *root;
  size_t key_size;
  qsa_cmp_fn *key_cmp;
};

struct qsa_bst *qsa_bst_create(size_t key_size, qsa_cmp_fn *key_cmp);

void qsa_bst_free(struct qsa_bst *t);

void qsa_bst_insert(struct qsa_bst *t, void *key);

void qsa_bst_delete(struct qsa_bst *t, void *key);

struct qsa_bst_node *qsa_bst_search(const struct qsa_bst *t, const void *key);

#endif /* QSA_BST_H */

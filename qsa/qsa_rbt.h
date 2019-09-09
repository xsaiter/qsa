/*
 * red-black tree
 */

#ifndef QSA_RBT_H
#define QSA_RBT_H

#include <stdbool.h>
#include <stddef.h>

#include "qsa_core.h"

enum qsa_rbt_colors { RED = 0, BLACK = 1 };

struct qsa_rbt_node {
  void *key;
  enum qsa_rbt_colors color;
  struct qsa_rbt_node *left;
  struct qsa_rbt_node *right;
  struct qsa_rbt_node *parent;
};

struct qsa_rbt {
  struct qsa_rbt_node *root;
  struct qsa_rbt_node *nil;
  size_t key_size;
  qsa_cmp_fn *key_cmp;
};

struct qsa_rbt *qsa_rbt_create(size_t key_size, qsa_cmp_fn *key_cmp);

void qsa_rbt_free(struct qsa_rbt *t);

struct qsa_rbt_node *qsa_rbt_search(const struct qsa_rbt *t, const void *key);

void qsa_rbt_insert(struct qsa_rbt *t, void *key);

#endif /* QSA_RBT_H */

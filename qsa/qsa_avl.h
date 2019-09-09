#ifndef QSA_AVL_H
#define QSA_AVL_H

#include <stdbool.h>
#include <stddef.h>

#include "qsa_core.h"

struct qsa_avl_node {
  void *data;
  struct qsa_avl_node *left;
  struct qsa_avl_node *right;
  int height;
};

struct qsa_avl {
  struct qsa_avl_node *root;
  size_t data_size;
  qsa_cmp_fn *cmp_data;
};

struct qsa_avl *qsa_avl_create(size_t data_size, qsa_cmp_fn *cmp_data);

void qsa_avl_free(struct qsa_avl *t);

void qsa_avl_insert(struct qsa_avl *t, void *data);

struct qsa_avl_node *qsa_avl_search(struct qsa_avl *t, void *data);

void qsa_avl_print(struct qsa_avl *t, void (*display)(void *data));

#endif /* QSA_AVL_H */

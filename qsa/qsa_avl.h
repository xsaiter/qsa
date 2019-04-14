#ifndef QSA_AVL_H
#define QSA_AVL_H

#include <stdbool.h>
#include <stddef.h>

#include "qsa_core.h"

typedef struct qsa_avl_node_s {
  void *data;
  struct qsa_avl_node_s *left;
  struct qsa_avl_node_s *right;
  int height;
} qsa_avl_node_s;

typedef struct {
  qsa_avl_node_s *root;
  size_t data_size;
  qsa_cmp_fn *cmp_data;
} qsa_avl_s;

qsa_avl_s *qsa_avl_create(size_t data_size, qsa_cmp_fn *cmp_data);

void qsa_avl_free(qsa_avl_s *t);

void qsa_avl_insert(qsa_avl_s *t, void *data);

qsa_avl_node_s *qsa_avl_search(qsa_avl_s *t, void *data);

void qsa_avl_print(qsa_avl_s *t, void (*display)(void *data));

#endif /* QSA_AVL_H */

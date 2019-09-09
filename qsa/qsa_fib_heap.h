/*
 * Fibonacci heap
 */

#include "qsa_core.h"

#ifndef QSA_FIB_HEAP_H
#define QSA_FIB_HEAP_H

struct qsa_fib_heap_node {
  struct qsa_fib_heap_node *parent;
  struct qsa_fib_heap_node *child;
};

struct qsa_fib_heap {
  size_t elem_size;
  void **elems;
  qsa_cmp_fn *cmp;
};

struct qsa_fib_heap *qsa_fib_heap_create(size_t elem_size, qsa_cmp_fn *cmp);

#endif /* QSA_FIB_HEAP_H */

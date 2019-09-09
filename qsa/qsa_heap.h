#ifndef QSA_HEAP_H
#define QSA_HEAP_H

#include "qsa_core.h"

struct qsa_heap {
  int capacity;
  int len;
  size_t elem_size;
  void **elems;
  qsa_cmp_fn *cmp;
};

struct qsa_heap *qsa_heap_create(int capacity, size_t elem_size,
                                 qsa_cmp_fn *cmp);

void qsa_heap_free(struct qsa_heap *h);

void qsa_heap_add(struct qsa_heap *h, void *elem);

void *qsa_heap_top(struct qsa_heap *h);

void qsa_heap_pop(struct qsa_heap *h);

bool qsa_heap_empty(struct qsa_heap *h);

#endif /* QSA_HEAP_H */

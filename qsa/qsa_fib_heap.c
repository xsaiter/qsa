#include "qsa_fib_heap.h"

struct qsa_fib_heap *qsa_fib_heap_create(size_t elem_size, qsa_cmp_fn *cmp) {
  struct qsa_fib_heap *h = qsa_malloc(sizeof(struct qsa_fib_heap));
  h->elem_size = elem_size;
  h->cmp = cmp;
  return h;
}

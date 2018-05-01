/*
 * Fibonacci heap
 */

#include "qsa_core.h"

#ifndef QSA_FIB_HEAP_H
#define QSA_FIB_HEAP_H

typedef struct {
    size_t elem_size;
    void **elems;
    qsa_compare_fn *cmp;
} qsa_fib_heap_s;

qsa_fib_heap_s *qsa_fib_heap_new(size_t elem_size, qsa_compare_fn *cmp);

#endif /* QSA_FIB_HEAP_H */
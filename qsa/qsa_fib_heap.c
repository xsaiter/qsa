#include "qsa_fib_heap.h"

qsa_fib_heap_s *qsa_fib_heap_new(size_t elem_size, qsa_cmp_fn *cmp)
{
    qsa_fib_heap_s *h = qsa_malloc(sizeof(qsa_fib_heap_s));
    
    h->elem_size = elem_size;
    h->cmp = cmp;
    
    return h;
}
#ifndef QSA_HEAP_H
#define QSA_HEAP_H

#include "qsa_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int capacity;
        int len;
        size_t elem_size;
        void **elems;
        q_compare_fn *cmp;
    } q_heap;

    q_heap *q_heap_new(int capacity, size_t elem_size, q_compare_fn *cmp);
    void q_heap_free(q_heap* h);
    void q_heap_add(q_heap *h, void *elem);
    void *q_heap_top(q_heap *h);
    void q_heap_pop(q_heap *h);
    bool q_heap_empty(q_heap *h);

#ifdef __cplusplus
}
#endif

#endif /* QSA_HEAP_H */
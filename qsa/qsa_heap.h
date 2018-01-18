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
        qsa_compare_fn *cmp;
    } qsa_heap_s;

    qsa_heap_s *qsa_heap_new(int capacity, size_t elem_size, qsa_compare_fn *cmp);
    void qsa_heap_free(qsa_heap_s* h);
    void qsa_heap_add(qsa_heap_s *h, void *elem);
    void *qsa_heap_top(qsa_heap_s *h);
    void qsa_heap_pop(qsa_heap_s *h);
    bool qsa_heap_empty(qsa_heap_s *h);

#ifdef __cplusplus
}
#endif

#endif /* QSA_HEAP_H */
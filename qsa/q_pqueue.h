#ifndef Q_PQUEUE_H
#define Q_PQUEUE_H

#include "q_list.h"
#include "q_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int capacity;
        size_t elt_size;
        int len;
        void **elts;
        compare_fn *compare;
    } q_pqueue;

    q_pqueue *q_pqueue_new(int capacity, size_t elt_size, compare_fn *compare);
    void q_pqueue_free(q_pqueue *q);
    void q_pqueue_insert(q_pqueue *q, const void *elt);
    void *q_pqueue_extract(q_pqueue *q);
    bool q_pqueue_empty(q_pqueue *q);    

#ifdef __cplusplus
}
#endif

#endif /* Q_PQUEUE_H */

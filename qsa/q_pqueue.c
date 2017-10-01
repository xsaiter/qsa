#include <stdlib.h>

#include "q_pqueue.h"

#define Q_LEFT(x) (2*(x) + 1)
#define Q_RIGHT(x) (2*(x) + 2)
#define Q_PARENT(x) ((x)/2)

static void q_heapify(q_pqueue *q, int i)
{

}

q_pqueue *q_pqueue_new(int capacity, size_t elt_size, compare_fn *compare)
{
    q_pqueue *q = xmalloc(sizeof (q_pqueue));

    q->capacity = capacity;
    q->elt_size = elt_size;
    q->len = 0;
    
    q->elts = xmalloc(q->capacity * sizeof (void*));
    for(int i = 0; i < q->capacity; ++i){
        q->elts[i] = xmalloc(q->elt_size);
    }
    
    q->compare = compare;    

    return q;
}

void q_pqueue_free(q_pqueue *q)
{
    free(q);
}

void q_pqueue_insert(q_pqueue *q, const void *elt)
{
}

void *q_pqueue_extract(q_pqueue *q)
{
    void *r = q->elts[0];

    q->elts[0] = q->elts[q->len - 1];
    q->len--;

    q_heapify(q, 0);

    return r;
}

bool q_pqueue_empty(q_pqueue *q)
{
    return q->len == 0;
}
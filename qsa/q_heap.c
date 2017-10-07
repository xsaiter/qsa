#include <string.h>
#include <stdlib.h>

#include "q_heap.h"

#define Q_LEFT(x) (2*(x) + 1)
#define Q_RIGHT(x) (2*(x) + 2)
#define Q_PARENT(x) ((x)/2)

q_heap *q_heap_new(int capacity, size_t elem_size, compare_fn *compare)
{
    q_heap *heap = xmalloc(sizeof (q_heap));

    heap->capacity = capacity;
    heap->len = 0;
    heap->elem_size = elem_size;
    heap->elems = xmalloc(heap->capacity * sizeof (void*));
    heap->compare = compare;

    return heap;
}

void q_heap_free(q_heap* h)
{
    for(int i = 0; i< h->len; ++i){
        free(h->elems[i]);
    }
    free(h);
}

inline static void swap(q_heap *h, int i, int j)
{
    void *buf = h->elems[i];
    h->elems[i] = h->elems[j];
    h->elems[j] = buf;
}

static void swim(q_heap *h, int i)
{
    while (i > 0 && h->compare(h->elems[i], h->elems[Q_PARENT(i)]) > 0) {
        swap(h, i, Q_PARENT(i));
        i = Q_PARENT(i);
    }
}

static void sink(q_heap *h, int i)
{

}

void q_heap_add(q_heap *h, void *elem)
{
    int pos = h->len++;

    h->elems[pos] = xmalloc(h->elem_size);
    memcpy(h->elems[pos], elem, h->elem_size);

    swim(h, pos);
}

void *q_heap_top(q_heap *h)
{
    return h->elems[0];
}

void *q_heap_extract(q_heap *h)
{
    void *res = h->elems[0];
    swap(h, 0, h->len - 1);
    sink(h, 0);
    return res;
}
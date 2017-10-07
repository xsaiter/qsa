#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <assert.h>

#include "q_heap.h"

#define Q_LEFT(x) (2*(x) + 1)
#define Q_RIGHT(x) (2*(x) + 2)
#define Q_PARENT(x) ((x)/2)

q_heap *q_heap_new(int capacity, size_t elem_size, compare_fn *compare)
{
    q_heap *h = xmalloc(sizeof (q_heap));

    h->capacity = capacity;
    h->len = 0;
    h->elem_size = elem_size;
    h->elems = xmalloc(h->capacity * sizeof (void*));
    for (int i = 0; i < h->capacity; ++i) {
        h->elems[i] = xmalloc(h->elem_size);
    }
    h->cmp = compare;

    return h;
}

void q_heap_free(q_heap* h)
{
    for (int i = 0; i < h->len; ++i) {
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
    while (i >= 0 && h->cmp(h->elems[i], h->elems[Q_PARENT(i)]) > 0) {
        swap(h, i, Q_PARENT(i));
        i = Q_PARENT(i);
    }
}

static void sink(q_heap *h, int i)
{
    while (Q_LEFT(i) < h->len) {
        int l = Q_LEFT(i);
        int r = Q_RIGHT(i);
        int x = r;

        if (h->cmp(h->elems[l], h->elems[r]) > 0) {
            x = l;
        }

        if (h->cmp(h->elems[i], h->elems[x]) > 0) {
            break;
        }
        
        swap(h, i, x);

        i = x;
    }
}

void q_heap_add(q_heap *h, void *elem)
{
    memcpy(h->elems[h->len++], elem, h->elem_size);
    swim(h, h->len - 1);
}

void *q_heap_top(q_heap *h)
{
    assert(!q_heap_empty(h));
    return h->elems[0];
}

void *q_heap_extract(q_heap *h)
{
    void *res = h->elems[0];
    swap(h, 0, h->len--);
    sink(h, 0);
    return res;
}

bool q_heap_empty(q_heap *h)
{
    return h->len == 0;
}
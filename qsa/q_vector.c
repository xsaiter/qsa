#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"q_vector.h"
#include "q_utils.h"

q_vector *q_vector_new(size_t capacity, size_t elem_size)
{
    q_vector *v = xmalloc(sizeof (q_vector));

    v->len = 0;
    v->capacity = capacity;
    v->elems = xmalloc(v->capacity * sizeof (void*));
    for (size_t i = 0; i < v->capacity; ++i) {
        v->elems[i] = xmalloc(elem_size);
    }
    v->elem_size = elem_size;

    return v;
}

inline q_vector *q_vector_new_int(size_t capacity)
{
    return q_vector_new(capacity, sizeof (int));
}

void q_vector_free(q_vector *v)
{
    free(v->elems);
    free(v);
}

static void q_vector_resize(q_vector *v, int new_capacity)
{
    void **elems = realloc(v->elems, new_capacity * sizeof (void*));
    if (elems) {
        for (size_t i = v->capacity; i < new_capacity; ++i) {
            elems[i] = xmalloc(v->elem_size);
        }
        v->elems = elems;
        v->capacity = new_capacity;
    }
}

void q_vector_add(q_vector *v, void *elem)
{
    int elt = *(int*) elem;
    if (v->len == v->capacity) {
        q_vector_resize(v, v->capacity * 2);
    }
    memcpy(v->elems[v->len++], elem, v->elem_size);
}

void q_vector_set(q_vector *v, size_t index, void *elem)
{
    memcpy(v->elems[index], elem, v->elem_size);
}

void *q_vector_get(q_vector *v, size_t index)
{
    return v->elems[index];
}

void q_vector_for_each(q_vector *v, void (*f)(void* elem))
{
    for (size_t i = 0; i < v->len; ++i) {
        f(v->elems[i]);
    }
}
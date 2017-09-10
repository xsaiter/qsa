#include <stdio.h>
#include <stdlib.h>

#include"q_vector.h"
#include "q_utils.h"

q_vector *q_vector_new(size_t capacity)
{
    q_vector *v = xmalloc(sizeof(q_vector));
    
    v->len = 0;
    v->capacity = capacity;
    v->elems = malloc(v->capacity * sizeof (void*));
    
    return v;
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
        v->elems = elems;
        v->capacity = new_capacity;
    }
}

void q_vector_add(q_vector *v, void *elem)
{
    if (v->len == v->capacity) {
        q_vector_resize(v, v->capacity * 2);
    }
    v->elems[v->len++] = elem;
}

void q_vector_set(q_vector *v, size_t index, void *elem)
{
    v->elems[index] = elem;
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
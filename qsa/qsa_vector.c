#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsa_core.h"
#include "qsa_vector.h"

struct qsa_vector *qsa_vector_create(size_t capacity, size_t elem_size) {
  struct qsa_vector *v = qsa_malloc(sizeof(struct qsa_vector));

  v->len = 0;
  v->capacity = capacity;
  v->elems = qsa_malloc(v->capacity * sizeof(void *));

  for (size_t i = 0; i < v->capacity; ++i) {
    v->elems[i] = qsa_malloc(elem_size);
  }

  v->elem_size = elem_size;

  return v;
}

void qsa_vector_free(struct qsa_vector *v) {
  free(v->elems);
  free(v);
}

static void qsa_vector_resize(struct qsa_vector *v, int new_capacity) {
  void **elems = realloc(v->elems, new_capacity * sizeof(void *));
  if (elems) {
    for (size_t i = v->capacity; i < new_capacity; ++i) {
      elems[i] = qsa_malloc(v->elem_size);
    }
    v->elems = elems;
    v->capacity = new_capacity;
  }
}

void qsa_vector_add(struct qsa_vector *v, void *elem) {
  if (v->len == v->capacity) {
    qsa_vector_resize(v, v->capacity * 2);
  }
  memcpy(v->elems[v->len++], elem, v->elem_size);
}

void qsa_vector_set(struct qsa_vector *v, size_t index, void *elem) {
  memcpy(v->elems[index], elem, v->elem_size);
}

void *qsa_vector_get(struct qsa_vector *v, size_t index) {
  return v->elems[index];
}

void qsa_vector_for_each(struct qsa_vector *v, void (*f)(void *elem)) {
  for (size_t i = 0; i < v->len; ++i) {
    f(v->elems[i]);
  }
}

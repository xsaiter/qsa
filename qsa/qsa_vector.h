#ifndef QSA_VECTOR_H
#define QSA_VECTOR_H

#include <stddef.h>

struct qsa_vector {
  void **elems;
  size_t len;
  size_t capacity;
  size_t elem_size;
};

struct qsa_vector *qsa_vector_create(size_t capacity, size_t elem_size);

void qsa_vector_free(struct qsa_vector *v);

void qsa_vector_add(struct qsa_vector *v, void *elem);

void qsa_vector_set(struct qsa_vector *v, size_t index, void *elem);

void *qsa_vector_get(struct qsa_vector *v, size_t index);

void qsa_vector_for_each(struct qsa_vector *v, void (*f)(void *elem));

#endif /* QSA_VECTOR_H */

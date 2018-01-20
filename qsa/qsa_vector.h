#ifndef QSA_VECTOR_H
#define QSA_VECTOR_H

#include <stddef.h>

typedef struct {
    void **elems;
    size_t len;
    size_t capacity;
    size_t elem_size;
} qsa_vector_s;

qsa_vector_s *qsa_vector_new(size_t capacity, size_t elem_size);
void qsa_vector_free(qsa_vector_s *v);
void qsa_vector_add(qsa_vector_s *v, void *elem);
void qsa_vector_set(qsa_vector_s *v, size_t index, void *elem);
void *qsa_vector_get(qsa_vector_s *v, size_t index);
void qsa_vector_for_each(qsa_vector_s *v, void (*f)(void* elem));

qsa_vector_s *qsa_vector_new_int(size_t capacity);

#endif /* QSA_VECTOR_H */


#ifndef QSA_STACK_H
#define QSA_STACK_H

#include <stdbool.h>
#include "qsa_list.h"

typedef struct {
    qsa_list_s *list;
} qsa_stack_s;

qsa_stack_s *qsa_stack_create(size_t data_size);

void qsa_stack_free(qsa_stack_s *s);

bool qsa_stack_empty(qsa_stack_s *s);

void qsa_stack_push(qsa_stack_s *s, void *data);

void *qsa_stack_pop(qsa_stack_s *s);

#endif /* QSA_STACK_H */


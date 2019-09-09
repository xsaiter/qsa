#ifndef QSA_STACK_H
#define QSA_STACK_H

#include "qsa_list.h"
#include <stdbool.h>

struct qsa_stack {
  struct qsa_list *list;
};

struct qsa_stack *qsa_stack_create(size_t data_size);

void qsa_stack_free(struct qsa_stack *s);

bool qsa_stack_empty(struct qsa_stack *s);

void qsa_stack_push(struct qsa_stack *s, void *data);

void *qsa_stack_pop(struct qsa_stack *s);

#endif /* QSA_STACK_H */

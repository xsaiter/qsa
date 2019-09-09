#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "qsa_stack.h"
#include "qsa_utils.h"

struct qsa_stack *qsa_stack_create(size_t data_size) {
  struct qsa_stack *s = qsa_malloc(sizeof(struct qsa_stack));
  s->list = qsa_list_create(data_size);
  return s;
}

void qsa_stack_free(struct qsa_stack *s) {
  qsa_list_free(s->list);
  free(s);
}

void qsa_stack_push(struct qsa_stack *s, void *data) {
  qsa_list_prepend(s->list, data);
}

bool qsa_stack_empty(struct qsa_stack *s) { return qsa_list_empty(s->list); }

void *qsa_stack_pop(struct qsa_stack *s) {
  struct qsa_list_node *head = s->list->head;
  if (!head) {
    return NULL;
  }
  void *ret = head->data;
  qsa_list_remove_node(s->list, head);
  return ret;
}

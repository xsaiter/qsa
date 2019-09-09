#ifndef QSA_LIST_H
#define QSA_LIST_H

#include <stdbool.h>
#include <stddef.h>

#include "qsa_core.h"

struct qsa_list_node {
  void *data;
  struct qsa_list_node *next;
  struct qsa_list_node *prev;
};

struct qsa_list {
  struct qsa_list_node *head;
  struct qsa_list_node *tail;
  size_t len;
  size_t data_size;
};

struct qsa_list *qsa_list_create(size_t data_size);

void qsa_list_free(struct qsa_list *list);

void qsa_list_prepend(struct qsa_list *list, void *data);

void qsa_list_append(struct qsa_list *list, void *data);

bool qsa_list_remove(struct qsa_list *list, void *data);

void qsa_list_remove_node(struct qsa_list *list, struct qsa_list_node *x);

struct qsa_list_node *qsa_list_find_by(struct qsa_list *list, void *data,
                                       qsa_eq_fn *eq);

struct qsa_list_node *qsa_list_find(struct qsa_list *list, void *data);

void qsa_list_for_each(struct qsa_list *list, qsa_action_fn *f);

bool qsa_list_empty(struct qsa_list *list);

#endif /* QSA_LIST_H */

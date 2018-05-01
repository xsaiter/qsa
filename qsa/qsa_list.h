#ifndef QSA_LIST_H
#define QSA_LIST_H

#include <stddef.h>
#include <stdbool.h>

#include "qsa_core.h"

typedef struct qsa_list_node_s {
    void *data;
    struct qsa_list_node_s *next;
    struct qsa_list_node_s *prev;
} qsa_list_node_s;

typedef struct {
    qsa_list_node_s *head;
    qsa_list_node_s *tail;
    size_t len;
    size_t data_size;
} qsa_list_s;

qsa_list_s *qsa_list_new(size_t data_size);

void qsa_list_free(qsa_list_s *list);

void qsa_list_prepend(qsa_list_s *list, void *data);

void qsa_list_append(qsa_list_s *list, void *data);

bool qsa_list_remove(qsa_list_s *list, void *data);

void qsa_list_remove_node(qsa_list_s *list, qsa_list_node_s *node);

qsa_list_node_s *qsa_list_find_by(qsa_list_s *list, void *data, qsa_eq_fn *eq);

qsa_list_node_s *qsa_list_find(qsa_list_s *list, void *data);

void qsa_list_for_each(qsa_list_s *list, qsa_action_fn *f);

bool qsa_list_empty(qsa_list_s *list);

#endif /* QSA_LIST_H */

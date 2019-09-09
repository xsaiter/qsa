#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsa_list.h"
#include "qsa_utils.h"

struct qsa_list *qsa_list_create(size_t data_size) {
  struct qsa_list *list = qsa_malloc(sizeof(struct qsa_list));
  list->len = 0;
  list->data_size = data_size;
  list->head = list->tail = NULL;
  return list;
}

static struct qsa_list_node *qsa_list_node_create(struct qsa_list *list,
                                                  void *data) {
  struct qsa_list_node *x = qsa_malloc(sizeof(struct qsa_list_node));
  x->data = qsa_malloc(list->data_size);
  memcpy(x->data, data, list->data_size);
  return x;
}

void qsa_list_free(struct qsa_list *list) {
  struct qsa_list_node *e = list->head;
  while (e) {
    free(e);
    e = e->next;
  }
  free(list);
}

void qsa_list_prepend(struct qsa_list *list, void *data) {
  struct qsa_list_node *x = qsa_list_node_create(list, data);
  if (list->len == 0) {
    list->head = list->tail = x;
    x->prev = x->next = NULL;
  } else {
    x->prev = NULL;
    x->next = list->head;
    list->head->prev = x;
    list->head = x;
  }
  list->len++;
}

void qsa_list_append(struct qsa_list *list, void *data) {
  struct qsa_list_node *x = qsa_list_node_create(list, data);
  if (list->len == 0) {
    list->head = list->tail = x;
    x->prev = x->next = NULL;
  } else {
    x->next = NULL;
    x->prev = list->tail;
    list->tail->next = x;
    list->tail = x;
  }
  list->len++;
}

bool qsa_list_remove(struct qsa_list *list, void *data) {
  struct qsa_list_node *x = list->head;
  while (x) {
    if (x->data == data) {
      qsa_list_remove_node(list, x);
      free(data);
      return true;
    }
    x = x->next;
  }
  return false;
}

void qsa_list_remove_node(struct qsa_list *list, struct qsa_list_node *x) {
  if (!list || !x) {
    return;
  }

  if (x->prev) {
    x->prev->next = x->next;
  } else {
    list->head = x->next;
  }

  if (x->next) {
    x->next->prev = x->prev;
  } else {
    list->tail = x->prev;
  }

  list->len--;
}

struct qsa_list_node *qsa_list_find_by(struct qsa_list *list, void *data,
                                       qsa_eq_fn *eq) {
  struct qsa_list_node *x;
  x = list->head;
  while (x) {
    if (eq(x->data, data)) {
      return x;
    }
    x = x->next;
  }
  return NULL;
}

struct qsa_list_node *qsa_list_find(struct qsa_list *list, void *data) {
  struct qsa_list_node *x;
  x = list->head;
  while (x) {
    if (x->data == data) {
      return x;
    }
    x = x->next;
  }
  return NULL;
}

void qsa_list_for_each(struct qsa_list *list, qsa_action_fn *f) {
  struct qsa_list_node *cur = list->head;
  while (cur) {
    f(cur->data);
    cur = cur->next;
  }
}

bool qsa_list_empty(struct qsa_list *list) { return list->len == 0; }

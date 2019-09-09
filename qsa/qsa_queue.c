#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "qsa_queue.h"
#include "qsa_utils.h"

struct qsa_queue *qsa_queue_create(size_t data_size) {
  struct qsa_queue *q = qsa_malloc(sizeof(struct qsa_queue));
  q->list = qsa_list_create(data_size);
  return q;
}

struct qsa_queue *qsa_queue_create_int(void) {
  return qsa_queue_create(sizeof(int));
}

void qsa_queue_free(struct qsa_queue *q) {
  qsa_list_free(q->list);
  free(q);
}

void qsa_queue_enq(struct qsa_queue *q, void *data) {
  return qsa_list_append(q->list, data);
}

void *qsa_queue_deq(struct qsa_queue *q) {
  struct qsa_list_node *head = q->list->head;
  if (!head) {
    return NULL;
  }
  void *ret = head->data;
  qsa_list_remove_node(q->list, head);
  return ret;
}

bool qsa_queue_empty(struct qsa_queue *q) { return qsa_list_empty(q->list); }

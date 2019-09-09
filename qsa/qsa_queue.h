#ifndef QSA_QUEUE_H
#define QSA_QUEUE_H

#include "qsa_list.h"

struct qsa_queue {
  struct qsa_list *list;
};

struct qsa_queue *qsa_queue_create(size_t data_size);

void qsa_queue_free(struct qsa_queue *q);

void qsa_queue_enq(struct qsa_queue *q, void *data);

void *qsa_queue_deq(struct qsa_queue *q);

bool qsa_queue_empty(struct qsa_queue *q);

struct qsa_queue *qsa_queue_create_int(void);

#endif /* QSA_QUEUE_H */

#ifndef QSA_QUEUE_H
#define QSA_QUEUE_H

#include "qsa_list.h"

typedef struct {
  qsa_list_s *list;
} qsa_queue_s;

qsa_queue_s *qsa_queue_create(size_t data_size);

void qsa_queue_free(qsa_queue_s *q);

void qsa_queue_enq(qsa_queue_s *q, void *data);

void *qsa_queue_deq(qsa_queue_s *q);

bool qsa_queue_empty(qsa_queue_s *q);

qsa_queue_s *qsa_queue_create_int();

#endif /* QSA_QUEUE_H */

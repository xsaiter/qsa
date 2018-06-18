#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "qsa_queue.h"
#include "qsa_utils.h"

qsa_queue_s *qsa_queue_create(size_t data_size)
{
    qsa_queue_s *q = qsa_malloc(sizeof (qsa_queue_s));
    q->list = qsa_list_create(data_size);
    return q;
}

qsa_queue_s *qsa_queue_create_int()
{
    return qsa_queue_create(sizeof (int));
}

void qsa_queue_free(qsa_queue_s *q)
{
    qsa_list_free(q->list);
    free(q);
}

void qsa_queue_enq(qsa_queue_s *q, void *data)
{
    return qsa_list_append(q->list, data);
}

void *qsa_queue_deq(qsa_queue_s *q)
{
    qsa_list_node_s *head = q->list->head;
    if (!head) {
        return NULL;
    }
    void *ret = head->data;
    qsa_list_remove_node(q->list, head);
    return ret;
}

bool qsa_queue_empty(qsa_queue_s *q)
{
    return qsa_list_empty(q->list);
}

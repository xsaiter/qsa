#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "q_queue.h"

void q_queue_init(q_queue *q){    
    q->list = malloc(sizeof(q_list));
    q_list_init(q->list);
}

void q_queue_destroy(q_queue *q)
{
    q_list_free(q->list);
    free(q->list);
}

void q_queue_enq(q_queue *q, void *data)
{
    return q_list_append(q->list, data);
}

void *q_queue_deq(q_queue *q)
{
    q_list_node *head = q->list->head;
    if (!head) {
        return NULL;
    }
    void *ret = head->data;
    q_list_remove_node(q->list, head);
    return ret;
}

bool q_queue_empty(q_queue *q)
{
    return q_list_empty(q->list);
}

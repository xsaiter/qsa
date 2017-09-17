#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "q_queue.h"
#include "q_utils.h"

q_queue *q_queue_new(size_t data_size){    
    q_queue *q = xmalloc(sizeof(q_queue));    
    q->list = q_list_new(data_size);
    return q;
}

inline q_queue *q_queue_new_int(){
    return q_queue_new(sizeof(int));
}

void q_queue_free(q_queue *q)
{
    q_list_free(q->list);
    free(q);
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

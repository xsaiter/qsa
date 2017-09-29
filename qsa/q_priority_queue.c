#include <stdlib.h>

#include "q_priority_queue.h"

q_priority_queue *q_priority_queue_new(int data_size)
{
    q_priority_queue *q = xmalloc(sizeof (q_priority_queue));

    q->list = q_list_new(data_size);

    return q;
}

void q_priority_queue_free(q_priority_queue *q)
{
    q_list_free(q->list);
    free(q);
}

void q_priority_queue_add(q_priority_queue *q, void *data)
{
    q_list_prepend(q->list, data);
}

void *q_priority_queue_extract(q_priority_queue *q)
{
    q_list_node *e = q->list->head;
    while(e){
        e = e->next;
    }
}


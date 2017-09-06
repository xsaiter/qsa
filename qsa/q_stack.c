#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "q_stack.h"

void q_stack_init(q_stack *s){
    s->list = malloc(sizeof(q_list));
    q_list_init(s->list);
}

void q_stack_destroy(q_stack *s)
{
    q_list_destroy(s->list);
    free(s->list);
}

void q_stack_push(q_stack *s, void *data)
{
    q_list_prepend(s->list, data);
}

bool q_stack_empty(q_stack *s)
{
    return q_list_empty(s->list);
}

void *q_stack_pop(q_stack *s)
{
    q_list_node *head = s->list->head;
    if (!head) {
        return NULL;
    }
    void *ret = head->data;
    q_list_remove_node(s->list, head);
    return ret;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "q_stack.h"
#include "q_utils.h"

q_stack *q_stack_new(){
    q_stack *s = xmalloc(sizeof(q_stack));    
    s->list = q_list_new();        
    return s;
}

void q_stack_free(q_stack *s)
{
    q_list_free(s->list);
    free(s);
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
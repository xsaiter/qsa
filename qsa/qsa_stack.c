#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "qsa_stack.h"
#include "qsa_utils.h"

qsa_stack_s *qsa_stack_new(size_t data_size)
{
    qsa_stack_s *s = qsa_malloc(sizeof (qsa_stack_s));
    s->list = qsa_list_new(data_size);
    return s;
}

void qsa_stack_free(qsa_stack_s *s)
{
    qsa_list_free(s->list);
    free(s);
}

void qsa_stack_push(qsa_stack_s *s, void *data)
{
    qsa_list_prepend(s->list, data);
}

bool qsa_stack_empty(qsa_stack_s *s)
{
    return qsa_list_empty(s->list);
}

void *qsa_stack_pop(qsa_stack_s *s)
{
    qsa_list_node_s *head = s->list->head;
    if (!head) {
        return NULL;
    }
    void *ret = head->data;
    qsa_list_remove_node(s->list, head);
    return ret;
}
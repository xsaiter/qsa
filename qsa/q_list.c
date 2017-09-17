#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "q_list.h"
#include "q_utils.h"

q_list *q_list_new(size_t data_size)
{
    q_list *list = xmalloc(sizeof (q_list));

    list->len = 0;
    list->data_size = data_size;
    list->head = list->tail = NULL;

    return list;
}

q_list *q_list_new_int()
{
    return q_list_new(sizeof (int));
}

static q_list_node *node_new(q_list *list, void *data)
{
    q_list_node *node = xmalloc(sizeof (q_list_node));
    node->data = xmalloc(list->data_size);
    memcpy(node->data, data, list->data_size);
    return node;
}

void q_list_free(q_list *list)
{
    q_list_node *e = list->head;
    while (e) {
        free(e);
        e = e->next;
    }

    free(list);
}

void q_list_prepend(q_list *list, void *data)
{
    q_list_node *node = node_new(list, data);

    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }

    list->len++;
}

void q_list_append(q_list *list, void *data)
{
    q_list_node *node = node_new(list, data);

    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->next = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }

    list->len++;
}

bool q_list_remove(q_list *list, void *data)
{
    q_list_node *cur = list->head;

    while (cur) {
        if (cur->data == data) {
            q_list_remove_node(list, cur);
            free(data);
            return true;
        }
        cur = cur->next;
    }

    return false;
}

void q_list_remove_node(q_list *list, q_list_node *node)
{
    if (!list || !node) {
        return;
    }

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    list->len--;
}

q_list_node *q_list_find_by(q_list *list, void *data, bool(*equals)(void *a, void *b))
{
    q_list_node *cur;
    cur = list->head;
    while (cur) {
        if (equals(cur->data, data)) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

q_list_node *q_list_find(q_list *list, void *data)
{
    q_list_node *cur;
    cur = list->head;
    while (cur) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void q_list_for_each(q_list *list, void (*f)(void *data))
{
    q_list_node *cur = list->head;
    while (cur) {
        f(cur->data);
        cur = cur->next;
    }
}

bool q_list_empty(q_list *list)
{
    return list->len == 0;
}
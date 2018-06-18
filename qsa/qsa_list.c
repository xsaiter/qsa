#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "qsa_list.h"
#include "qsa_utils.h"

qsa_list_s *qsa_list_create(size_t data_size)
{
    qsa_list_s *list = qsa_malloc(sizeof (qsa_list_s));

    list->len = 0;
    list->data_size = data_size;
    list->head = list->tail = NULL;

    return list;
}

static qsa_list_node_s *qsa_list_node_create(qsa_list_s *list, void *data)
{
    qsa_list_node_s *x = qsa_malloc(sizeof (qsa_list_node_s));
    x->data = qsa_malloc(list->data_size);
    memcpy(x->data, data, list->data_size);
    return x;
}

void qsa_list_free(qsa_list_s *list)
{
    qsa_list_node_s *e = list->head;
    while (e) {
        free(e);
        e = e->next;
    }

    free(list);
}

void qsa_list_prepend(qsa_list_s *list, void *data)
{
    qsa_list_node_s *x = qsa_list_node_create(list, data);

    if (list->len == 0) {
        list->head = list->tail = x;
        x->prev = x->next = NULL;
    } else {
        x->prev = NULL;
        x->next = list->head;
        list->head->prev = x;
        list->head = x;
    }

    list->len++;
}

void qsa_list_append(qsa_list_s *list, void *data)
{
    qsa_list_node_s *x = qsa_list_node_create(list, data);

    if (list->len == 0) {
        list->head = list->tail = x;
        x->prev = x->next = NULL;
    } else {
        x->next = NULL;
        x->prev = list->tail;
        list->tail->next = x;
        list->tail = x;
    }

    list->len++;
}

bool qsa_list_remove(qsa_list_s *list, void *data)
{
    qsa_list_node_s *x = list->head;

    while (x) {
        if (x->data == data) {
            qsa_list_remove_node(list, x);
            free(data);
            return true;
        }
        x = x->next;
    }

    return false;
}

void qsa_list_remove_node(qsa_list_s *list, qsa_list_node_s *x)
{
    if (!list || !x) {
        return;
    }

    if (x->prev) {
        x->prev->next = x->next;
    } else {
        list->head = x->next;
    }

    if (x->next) {
        x->next->prev = x->prev;
    } else {
        list->tail = x->prev;
    }

    list->len--;
}

qsa_list_node_s *qsa_list_find_by(qsa_list_s *list, void *data, qsa_eq_fn *eq)
{
    qsa_list_node_s *x;
    x = list->head;
    while (x) {
        if (eq(x->data, data)) {
            return x;
        }
        x = x->next;
    }
    return NULL;
}

qsa_list_node_s *qsa_list_find(qsa_list_s *list, void *data)
{
    qsa_list_node_s *x;
    x = list->head;
    while (x) {
        if (x->data == data) {
            return x;
        }
        x = x->next;
    }
    return NULL;
}

void qsa_list_for_each(qsa_list_s *list, qsa_action_fn *f)
{
    qsa_list_node_s *cur = list->head;
    while (cur) {
        f(cur->data);
        cur = cur->next;
    }
}

bool qsa_list_empty(qsa_list_s *list)
{
    return list->len == 0;
}
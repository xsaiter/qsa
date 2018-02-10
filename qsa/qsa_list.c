#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "qsa_list.h"
#include "qsa_utils.h"

qsa_list_s *qsa_list_new(size_t data_size)
{
    qsa_list_s *list = qsa_malloc(sizeof (qsa_list_s));

    list->len = 0;
    list->data_size = data_size;
    list->head = list->tail = NULL;

    return list;
}

static qsa_list_node_s *node_new(qsa_list_s *list, void *data)
{
    qsa_list_node_s *node = qsa_malloc(sizeof (qsa_list_node_s));
    node->data = qsa_malloc(list->data_size);
    memcpy(node->data, data, list->data_size);
    return node;
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
    qsa_list_node_s *node = node_new(list, data);

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

void qsa_list_append(qsa_list_s *list, void *data)
{
    qsa_list_node_s *node = node_new(list, data);

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

bool qsa_list_remove(qsa_list_s *list, void *data)
{
    qsa_list_node_s *cur = list->head;

    while (cur) {
        if (cur->data == data) {
            qsa_list_remove_node(list, cur);
            free(data);
            return true;
        }
        cur = cur->next;
    }

    return false;
}

void qsa_list_remove_node(qsa_list_s *list, qsa_list_node_s *node)
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

qsa_list_node_s *qsa_list_find_by(qsa_list_s *list, void *data, qsa_eq_fn *eq)
{
    qsa_list_node_s *cur;
    cur = list->head;
    while (cur) {
        if (eq(cur->data, data)) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

qsa_list_node_s *qsa_list_find(qsa_list_s *list, void *data)
{
    qsa_list_node_s *cur;
    cur = list->head;
    while (cur) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
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
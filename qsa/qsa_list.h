#ifndef QSA_LIST_H
#define QSA_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include "qsa_utils.h"

#ifdef __cplusplus
extern "C" {
#endif       
    typedef struct q_list_node {
        void *data;
        struct q_list_node *next;
        struct q_list_node *prev;
    } q_list_node;

    typedef struct {
        q_list_node *head;
        q_list_node *tail;
        size_t len;
        size_t data_size;
    } q_list;
    
    q_list *q_list_new(size_t data_size);
    void q_list_free(q_list *list);
    
    void q_list_prepend(q_list *list, void *data);
    void q_list_append(q_list *list, void *data);    
    
    bool q_list_remove(q_list *list, void *data);
    void q_list_remove_node(q_list *list, q_list_node *node);    
    
    q_list_node *q_list_find_by(q_list *list, void *data, q_equals_fn *equals);
    q_list_node *q_list_find(q_list *list, void *data);
    
    void q_list_for_each(q_list *list, void (*f)(void *data));    
    bool q_list_empty(q_list *list);
    
    q_list *q_list_new_int();

#ifdef __cplusplus
}
#endif

#endif /* QSA_LIST_H */


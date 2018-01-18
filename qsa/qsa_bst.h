/*
 * binary search tree
 */

#ifndef QSA_BST_H
#define QSA_BST_H

#include "qsa_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_bst_node {
        void *key;
        struct q_bst_node *parent;
        struct q_bst_node *left;
        struct q_bst_node *right;
    } q_bst_node;

    typedef struct {
        q_bst_node *root;
        size_t key_size;
        qsa_compare_fn *key_cmp;
    } q_bst;

    q_bst *q_bst_new(size_t key_size, qsa_compare_fn *key_cmp);
    void q_bst_free(q_bst *t);
    void q_bst_add(q_bst *t, void *key);
    void q_bst_remove(q_bst *t, void *key);
    q_bst_node *q_bst_find(q_bst *t, void *key);

#ifdef __cplusplus
}
#endif

#endif /* QSA_BST_H */
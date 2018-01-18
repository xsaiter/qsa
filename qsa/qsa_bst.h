/*
 * binary search tree
 */

#ifndef QSA_BST_H
#define QSA_BST_H

#include "qsa_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct qsa_bst_node_s {
        void *key;
        struct qsa_bst_node_s *parent;
        struct qsa_bst_node_s *left;
        struct qsa_bst_node_s *right;
    } qsa_bst_node_s;

    typedef struct {
        qsa_bst_node_s *root;
        size_t key_size;
        qsa_compare_fn *key_cmp;
    } qsa_bst_s;

    qsa_bst_s *qsa_bst_new(size_t key_size, qsa_compare_fn *key_cmp);
    void qsa_bst_free(qsa_bst_s *t);
    void qsa_bst_add(qsa_bst_s *t, void *key);
    void qsa_bst_remove(qsa_bst_s *t, void *key);
    qsa_bst_node_s *qsa_bst_find(qsa_bst_s *t, void *key);

#ifdef __cplusplus
}
#endif

#endif /* QSA_BST_H */
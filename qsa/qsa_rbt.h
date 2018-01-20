/*
 * red-black tree
 */

#ifndef QSA_RBT_H
#define QSA_RBT_H

#include <stddef.h>
#include <stdbool.h>

#include "qsa_core.h"

typedef enum {RED = 0, BKACK = 1} qsa_rbt_colors_s;

typedef struct qsa_rbt_node_s {
    void *key;
    qsa_rbt_colors_s color;
    bool nil;
    struct qsa_rbt_node_s *left;
    struct qsa_rbt_node_s *right;
    struct qsa_rbt_node_s *parent;   
} qsa_rbt_node_s;

typedef struct {
    qsa_rbt_node_s *root;
    qsa_rbt_node_s *nil;
    size_t key_size; 
    qsa_compare_fn *key_cmp;
} qsa_rbt_s;

qsa_rbt_s *qsa_rbt_new(size_t key_size, qsa_compare_fn *key_cmp);
void qsa_rbt_free(qsa_rbt_s *t);
void qsa_rbt_insert(qsa_rbt_s *t, const void *key);
qsa_rbt_node_s *qsa_rbt_search(const qsa_rbt_s *t, const void *key);

#endif /* QSA_RBT_H */


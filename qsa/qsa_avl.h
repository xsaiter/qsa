#ifndef QSA_AVL_H
#define QSA_AVL_H

#include <stddef.h>
#include <stdbool.h>

typedef struct qsa_avl_node_s{
    int data;
    struct qsa_avl_node_s *left;
    struct qsa_avl_node_s *right;
    int height;
} qsa_avl_node_s;

typedef struct{
    qsa_avl_node_s *root;
} qsa_avl_s;

qsa_avl_s *qsa_avl_new();

void qsa_avl_free(qsa_avl_s *self);

void qsa_avl_insert(qsa_avl_s *self, int data);

void qsa_avl_delete(qsa_avl_s *self, int data);

#endif /* QSA_AVL_H */


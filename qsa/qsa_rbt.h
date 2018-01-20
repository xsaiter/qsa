/*
 * red-black tree
 */

#ifndef QSA_RBT_H
#define QSA_RBT_H

typedef struct qsa_rbt_node_s {
    struct qsa_rbt_node_s *left;
    struct qsa_rbt_node_s *right;
    struct qsa_rbt_node_s *parent;
} qsa_rbt_node_s;

typedef struct {
    qsa_rbt_node_s *root;
} qsa_rbt_s;

#endif /* QSA_RBT_H */


/*
 * red-black tree
 */

#ifndef QSA_RBT_H
#define QSA_RBT_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_rbt_node {
        struct q_rbt_node *left, *right, *parent;
    } q_rbt_node;

    typedef struct {
        q_rbt_node *root;
    } q_rbt;


#ifdef __cplusplus
}
#endif

#endif /* QSA_RBT_H */


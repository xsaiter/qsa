/*
 * red-black tree
 */

#ifndef _QSA_RBT_H
#define _QSA_RBT_H

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

#endif /* _QSA_RBT_H */


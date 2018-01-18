/*
 * red-black tree
 */

#ifndef Q_RBT_H
#define Q_RBT_H

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

#endif /* Q_RBT_H */


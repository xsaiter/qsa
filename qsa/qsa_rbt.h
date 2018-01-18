/*
 * red-black tree
 */

#ifndef QSA_RBT_H
#define QSA_RBT_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct qsa_rbt_node_s {
        struct qsa_rbt_node_s *left, *right, *parent;
    } qsa_rbt_node_s;

    typedef struct {
        qsa_rbt_node_s *root;
    } qsa_rbt_s;


#ifdef __cplusplus
}
#endif

#endif /* QSA_RBT_H */


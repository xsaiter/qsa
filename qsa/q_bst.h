/*
 * binary search tree
 */
#ifndef Q_BST_H
#define Q_BST_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct q_bst_node {
        int key;
        struct q_bst_node *parent;
        struct q_bst_node *left;
        struct q_bst_node *right;
    } q_bst_node;

    typedef struct {
        q_bst_node *root;
    } q_bst;
            
    q_bst_node *q_bst_find(q_bst *tree, int key);
    void q_bst_add(q_bst *tree, int key);    
    void q_bst_remove(q_bst *tree, int key);        
    void q_bst_destroy(q_bst *tree);

#ifdef __cplusplus
}
#endif

#endif /* Q_BST_H */
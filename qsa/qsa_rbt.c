#include <assert.h>

#include "qsa_rbt.h"

qsa_rbt_s *qsa_rbt_new(size_t key_size, qsa_compare_fn *key_cmp)
{
    qsa_rbt_s *t = qsa_malloc(sizeof(qsa_rbt_s));
        
    t->key_size = key_size;
    t->key_cmp = key_cmp;
    
    t->root = NULL;
    
    qsa_rbt_node_s *nil = qsa_malloc(sizeof(qsa_rbt_node_s));
    
    
    
    t->nil = nil;    
    
    return t;
}

void qsa_rbt_left_rotate(qsa_rbt_s *t, qsa_rbt_node_s *x)
{    
    qsa_rbt_node_s *y = x->right;
    x->right = y->left;
}
#include "qsa_btree.h"

qsa_btree_s *qsa_btree_new(size_t min_degree, size_t key_size, qsa_compare_fn *cmp_keys)
{
    qsa_btree_s *t = qsa_malloc(sizeof(qsa_btree_s));
    
    t->min_degree = min_degree;
    t->key_size = key_size;
    t->cmp_keys = cmp_keys;
    
    return t;
}
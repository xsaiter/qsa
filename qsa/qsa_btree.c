#include "qsa_btree.h"

qsa_btree_s *qsa_btree_create(size_t degree)
{
    qsa_btree_s *t = qsa_malloc(sizeof (qsa_btree_s));

    t->degree = degree;
    t->max_ne = 2 * degree - 1;
    t->max_nc = t->max_ne + 1;
    t->root = NULL;

    return t;
}

static bool qsabtree_node_is_full(qsa_btree_s *t, qsa_btree_node_s *x)
{
    return x->n == t->max_ne;
}

static qsa_btree_entry_s *qsa_btree_entry_create(int key, int ptr)
{
    qsa_btree_entry_s *cell = qsa_malloc(sizeof (qsa_btree_entry_s));
    cell->key = key;
    cell->ptr = ptr;
    return cell;
}

static qsa_btree_node_s *qsa_btree_node_create(qsa_btree_s *t)
{
    qsa_btree_node_s *x = qsa_malloc(sizeof (qsa_btree_node_s));
    
    x->n = 0;
    x->e = qsa_malloc(sizeof (qsa_btree_entry_s) * t->max_ne);
    x->c = qsa_malloc(sizeof (qsa_btree_node_s) * t->max_nc);
    x->is_leaf = false;

    return x;
}

static void qsa_btree_insert_non_full(qsa_btree_node_s *x, int i){
}

void qsa_btree_insert(qsa_btree_s *t, int key, int ptr)
{    
}
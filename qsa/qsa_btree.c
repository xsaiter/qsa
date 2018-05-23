#include "qsa_btree.h"

qsa_btree_s *qsa_btree_create(size_t degree)
{
    qsa_btree_s *t = qsa_malloc(sizeof (qsa_btree_s));

    t->degree = degree;
    t->nce = 2 * degree - 1;
    t->nch = t->nce + 1;
    t->root = NULL;

    return t;
}

static bool qsabtree_node_is_full(qsa_btree_s *t, qsa_btree_node_s *x)
{
    return x->ncells == t->nce;
}

static qsa_btree_cell_s *qsa_btree_cell_create(int key, int ptr)
{
    qsa_btree_cell_s *cell = qsa_malloc(sizeof (qsa_btree_cell_s));
    cell->key = key;
    cell->ptr = ptr;
    return cell;
}

static qsa_btree_node_s *qsa_btree_node_create(qsa_btree_s *t)
{
    qsa_btree_node_s *node = qsa_malloc(sizeof (qsa_btree_node_s));

    node->parent = NULL;
    node->ncells = 0;
    node->cells = qsa_malloc(sizeof (qsa_btree_cell_s) * t->nce);
    node->children = qsa_malloc(sizeof (qsa_btree_node_s) * t->nch);
    node->is_leaf = false;

    return node;
}

void qsa_btree_insert(qsa_btree_s *t, int key, int ptr)
{

}
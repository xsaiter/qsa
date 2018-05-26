#include <stdlib.h>

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

void qsa_btree_free(qsa_btree_s *t)
{
    free(t);
}

static qsa_btree_node_s *qsa_btree_node_create(qsa_btree_s *t)
{
    qsa_btree_node_s *x = qsa_malloc(sizeof (qsa_btree_node_s));

    x->n = 0;
    x->e = qsa_malloc(sizeof (qsa_btree_entry_s*) * t->max_ne);
    x->c = qsa_malloc(sizeof (qsa_btree_node_s*) * t->max_nc);
    x->is_leaf = false;

    return x;
}

void qsa_btree_node_split_child(qsa_btree_s *t, qsa_btree_node_s *x, int i)
{
    size_t d = t->degree;

    qsa_btree_node_s *y = x->c[i];

    qsa_btree_node_s *z = qsa_btree_node_create(t);

    z->is_leaf = y->is_leaf;
    z->n = d - 1;

    for (int j = 0; j < d - 1; ++j) {
        z->e[j] = y->e[j + d];
    }

    if (!(y->is_leaf)) {
        for (int j = 0; j < d; ++j) {
            z->c[j] = y->c[j + d];
        }
    }

    y->n = d - 1;

    for (int j = x->n; j > i + 1; --j) {
        x->c[j + 1] = x->c[j];
    }

    x->c[i + 1] = z;

    for (int j = x->n; j > i; --j) {
        x->e[j + 1] = x->e[j];
    }

    x->e[i] = y->e[d];

    ++(x->n);
}

static bool qsa_btree_node_is_full(qsa_btree_s *t, qsa_btree_node_s *x)
{
    return x->n == t->max_ne;
}

static qsa_btree_entry_s *qsa_btree_entry_create(int key, int ptr)
{
    qsa_btree_entry_s *e = qsa_malloc(sizeof (qsa_btree_entry_s));

    e->key = key;
    e->ptr = ptr;

    return e;
}

static void qsa_btree_insert_non_full(qsa_btree_s *t, qsa_btree_node_s *x, int key, int ptr)
{
    int i = x->n - 1;

    if (x->is_leaf) {
        qsa_btree_entry_s *e = qsa_btree_entry_create(key, ptr);

        while (i >= 0 && x->e[i]->key > key) {
            x->e[i + 1] = x->e[i];
            --i;
        }

        ++i;
        x->e[i] = e;
        x->c[i] = NULL;
        ++(x->n);
    } else {
        while (i >= 0 && x->e[i]->key > key) {
            --i;
        }

        ++i;

        qsa_btree_node_s *c = x->c[i];

        bool is_full = qsa_btree_node_is_full(t, c);

        if (is_full) {
            qsa_btree_node_split_child(t, x, i);
            if (key > x->e[i]->key) {
                ++i;
            }
        }
    }

    qsa_btree_insert_non_full(t, x->c[i], key, ptr);
}

void qsa_btree_insert(qsa_btree_s *t, int key, int ptr)
{
    qsa_btree_node_s *r = t->root;

    bool is_full = qsa_btree_node_is_full(t, r);

    if (is_full) {
        qsa_btree_node_s *x = qsa_btree_node_create(t);

        x->is_leaf = false;
        x->n = 0;
        x->c[0] = r;

        t->root = x;

        qsa_btree_node_split_child(t, x, 0);

        qsa_btree_insert_non_full(t, t->root, key, ptr);
    } else {
        qsa_btree_insert_non_full(t, r, key, ptr);
    }
}
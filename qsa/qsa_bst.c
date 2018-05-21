#include <stdlib.h>
#include <string.h>

#include "qsa_core.h"
#include "qsa_bst.h"

qsa_bst_s *qsa_bst_new(size_t key_size, qsa_cmp_fn *key_cmp)
{
    qsa_bst_s *t = qsa_malloc(sizeof (qsa_bst_s));

    t->key_size = key_size;
    t->key_cmp = key_cmp;

    return t;
}

static qsa_bst_node_s *node_new(qsa_bst_s *t, void *key)
{
    qsa_bst_node_s *node = qsa_malloc(sizeof (qsa_bst_node_s));

    node->key = qsa_malloc(t->key_size);
    memcpy(node->key, key, t->key_size);

    return node;
}

void qsa_bst_free(qsa_bst_s *t)
{
    free(t);
}

static void add_node(qsa_bst_s *t, void *key, qsa_bst_node_s *x)
{
    if (t->key_cmp(x->key, key) == 0) {
        return;
    }

    if (t->key_cmp(x->key, key) > 0) {
        if (!x->left) {
            x->left = node_new(t, key);
        } else {
            add_node(t, key, x->left);
        }
    } else {
        if (!x->right) {
            x->right = node_new(t, key);
        } else {
            add_node(t, key, x->right);
        }
    }
}

void qsa_bst_insert(qsa_bst_s *t, void *key)
{
    if (!t->root) {
        t->root = node_new(t, key);
    } else {
        add_node(t, key, t->root);
    }
}

qsa_bst_node_s *qsa_bst_search(const qsa_bst_s *t, const void *key)
{
    qsa_bst_node_s *r = t->root;

    while (r) {
        int cmp = t->key_cmp(r->key, key);

        if (cmp == 0) {
            return r;
        }
        if (cmp > 0) {
            r = r->right;
        } else {
            r = r->left;
        }
    }

    return NULL;
}

static void transplant(qsa_bst_s *t, qsa_bst_node_s *a, qsa_bst_node_s *b)
{
    if (!a->parent) {
        t->root = b;
    } else if (a == a->parent->left) {
        a->parent->left = b;
    } else {
        a->parent->right = b;
    }

    if (b) {
        b->parent = a->parent;
    }
}

static qsa_bst_node_s *min_node(qsa_bst_node_s *x)
{
    qsa_bst_node_s *c = x;
    while ((c->left)) {
        c = c->left;
    }
    return c;
}

static void remove_node(qsa_bst_s *t, qsa_bst_node_s *x)
{
    if (!x->left && !x->right) {
        if (!x->parent) {
            t->root = NULL;
        } else {
            if (x->parent->right == x) {
                x->parent->right = NULL;
            } else if (x->parent->left == x) {
                x->parent->left = NULL;
            }
        }
    } else if (!x->left) {
        transplant(t, x, x->right);
    } else if (!x->right) {
        transplant(t, x, x->left);
    } else {
        qsa_bst_node_s *m = min_node(x->right);

        if (m->parent != x) {
            transplant(t, m, m->right);
            m->right = x->right;
            m->right->parent = m;
        }

        transplant(t, x, m);
        m->left = x->left;
        m->left->parent = m;
    }
}

static void _q_bst_remove(qsa_bst_s *t, void *key, qsa_bst_node_s *x)
{
    if (x) {
        int cmp = t->key_cmp(x->key, key);

        if (cmp > 0) {
            _q_bst_remove(t, key, x->left);
        } else if (cmp < 0) {
            _q_bst_remove(t, key, x->right);
        } else {
            remove_node(t, x);
        }
    }
}

void qsa_bst_delete(qsa_bst_s *t, void *key)
{
    _q_bst_remove(t, key, t->root);
}
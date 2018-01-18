#include <stdlib.h>
#include <string.h>

#include "qsa_utils.h"
#include "qsa_bst.h"

q_bst *q_bst_new(size_t key_size, q_compare_fn *key_cmp)
{
    q_bst *t = xmalloc(sizeof (q_bst));

    t->key_size = key_size;
    t->key_cmp = key_cmp;

    return t;
}

static q_bst_node *node_new(q_bst *t, void *key)
{
    q_bst_node *node = xmalloc(sizeof (q_bst_node));

    node->key = xmalloc(t->key_size);
    memcpy(node->key, key, t->key_size);

    return node;
}

void q_bst_free(q_bst *t)
{
    free(t);
}

static void add_node(q_bst *t, void *key, q_bst_node *x)
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

void q_bst_add(q_bst *t, void *key)
{
    if (!t->root) {
        t->root = node_new(t, key);
    } else {
        add_node(t, key, t->root);
    }
}

q_bst_node *q_bst_find(q_bst *t, void *key)
{
    q_bst_node *r = t->root;

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

static void transplant(q_bst *t, q_bst_node *a, q_bst_node *b)
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

static q_bst_node *min_node(q_bst_node *x)
{
    q_bst_node *c = x;
    while ((c->left)) {
        c = c->left;
    }
    return c;
}

static void remove_node(q_bst *t, q_bst_node *x)
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
        q_bst_node *m = min_node(x->right);

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

static void _q_bst_remove(q_bst *t, void *key, q_bst_node *x)
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

void q_bst_remove(q_bst *t, void *key)
{
    _q_bst_remove(t, key, t->root);
}
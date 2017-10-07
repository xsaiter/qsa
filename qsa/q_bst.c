#include <stdlib.h>

#include "q_utils.h"
#include "q_bst.h"

static q_bst_node *_q_bst_node_create(int key)
{
    q_bst_node *node = xmalloc(sizeof (q_bst_node));
    node->key = key;
    return node;
}

static void _q_add_node(q_bst *t, int key, q_bst_node *node)
{
    if (node->key == key) {
        return;
    }

    if (node->key > key) {
        if (!node->left) {
            node->left = _q_bst_node_create(key);
        } else {
            _q_add_node(t, key, node->left);
        }
    } else {
        if (!node->right) {
            node->right = _q_bst_node_create(key);
        } else {
            _q_add_node(t, key, node->right);
        }
    }
}

void q_bst_add(q_bst *t, int key)
{
    if (!t->root) {
        t->root = _q_bst_node_create(key);
    } else {
        _q_add_node(t, key, t->root);
    }
}

q_bst_node *q_bst_find(q_bst *t, int key)
{
    q_bst_node *r = t->root;

    while (r) {
        if (r->key == key) {
            return r;
        }
        if (r->key > key) {
            r = r->left;
        } else {
            r = r->left;
        }
    }

    return NULL;
}

static q_bst_node *min(q_bst_node *z)
{
    q_bst_node *x = z;
    while ((x->left)) {
        x = x->left;
    }
    return x;
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

static void _q_bst_remove_for(q_bst *t, q_bst_node *z)
{
    if (!z->left && !z->right) {
        if (!z->parent) {
            t->root = NULL;
        } else {
            if (z->parent->right == z) {
                z->parent->right = NULL;
            } else if (z->parent->left == z) {
                z->parent->left = NULL;
            }
        }
    } else if (!z->left) {
        transplant(t, z, z->right);
    } else if (!z->right) {
        transplant(t, z, z->left);
    } else {
        q_bst_node *m = min(z->right);

        if (m->parent != z) {
            transplant(t, m, m->right);
            m->right = z->right;
            m->right->parent = m;
        }

        transplant(t, z, m);
        m->left = z->left;
        m->left->parent = m;
    }
}

static void _q_bst_remove(q_bst *t, int key, q_bst_node *node)
{
    if (node) {
        if (node->key > key) {
            _q_bst_remove(t, key, node->left);
        } else if (node->key < key) {
            _q_bst_remove(t, key, node->right);
        } else {
            _q_bst_remove_for(t, node);
        }
    }
}

void q_bst_remove(q_bst *t, int key)
{
    _q_bst_remove(t, key, t->root);
}

void q_bst_destroy(q_bst *t)
{
}
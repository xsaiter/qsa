#include <assert.h>

#include "qsa_rbt.h"

static qsa_rbt_node_s *qsa_rbt_node_new(void *key, qsa_rbt_colors_s color)
{
    qsa_rbt_node_s *r = qsa_malloc(sizeof (qsa_rbt_node_s));
    r->key = key;
    r->color = color;
    r->parent = r->left = r->right = NULL;
    return r;
}

qsa_rbt_s *qsa_rbt_new(size_t key_size, qsa_cmp_fn *key_cmp)
{
    qsa_rbt_s *t = qsa_malloc(sizeof (qsa_rbt_s));

    t->key_size = key_size;
    t->key_cmp = key_cmp;
    t->root = NULL;

    qsa_rbt_node_s *nil = qsa_rbt_node_new(NULL, BLACK);        
    nil->parent = t->root;
    
    t->root->parent = nil;
    t->nil = nil;

    return t;
}

qsa_rbt_node_s *qsa_rbt_search(const qsa_rbt_s *t, const void *key)
{
    qsa_rbt_node_s *x = t->root;

    while (x) {
        int cmp = t->key_cmp(x->key, key);

        if (cmp == 0) {
            break;
        }

        if (cmp > 0) {
            x = x->right;
        } else {
            x = x->left;
        }
    }

    return x;
}

static void qsa_rbt_left_rotate(qsa_rbt_s *t, qsa_rbt_node_s *x)
{
    assert(x->right != t->nil);

    qsa_rbt_node_s *y = x->right;
    x->right = y->left;

    if (y->left != t->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == t->nil) {
        t->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;

    x->parent = y;
}

static void qsa_rbt_right_rotate(qsa_rbt_s *t, qsa_rbt_node_s *x)
{
    
}

static void qsa_rbt_insert_restore(qsa_rbt_s *t, qsa_rbt_node_s *z)
{
    qsa_rbt_node_s *y = NULL;

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else if (z == z->parent->right) {
                z = z->parent;
                qsa_rbt_left_rotate(t, z);
            }

            z->parent->color = BLACK;
            z->parent->parent->color = RED;
        }
    }
}

void qsa_rbt_insert(qsa_rbt_s *t, void *key)
{
    int cmp = 0;

    qsa_rbt_node_s *z = qsa_rbt_node_new(key, RED);

    qsa_rbt_node_s *y = t->nil;
    qsa_rbt_node_s *x = t->root;

    while (x != t->nil) {
        y = x;
        cmp = t->key_cmp(z->key, x->key);
        if (cmp < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    cmp = t->key_cmp(z->key, y->key);

    if (y == t->nil) {
        t->root = z;
    } else if (cmp < 0) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->left = t->nil;
    z->right = t->nil;
    z->color = RED;

    qsa_rbt_insert_restore(t, z);
}
#include <stdlib.h>

#include "qsa_avl.h"

#include "qsa_core.h"

qsa_avl_s *qsa_avl_new()
{
    qsa_avl_s *t = qsa_malloc(sizeof (qsa_avl_s));
    t->root = 0;
    return t;
}

void qsa_avl_free(qsa_avl_s *self)
{
    free(self);
}

void qsa_avl_print(qsa_avl_s *self)
{
}

void qsa_avl_insert(qsa_avl_s *self, int data)
{

}

static void qsa_avl_calculate_height(qsa_avl_node_s *x)
{
    int a, b;

    if (x->left) {
        a = x->left->height;
    } else {
        a = 0;
    }

    if (x->right) {
        b = x->right->height;
    } else {
        b = 0;
    }
    if (a > b) {
        x->height = a + 1;
    } else {
        x->height = b + 1;
    }
}

static int qsa_avl_get_balance(qsa_avl_node_s *x)
{
    int a, b;

    if (x->left) {
        a = x->left->height;
    } else {
        a = 0;
    }

    if (x->right) {
        b = x->right->height;
    } else {
        b = 0;
    }

    return b - a;
}

static void qsa_avl_turn_left(qsa_avl_node_s **x)
{
    qsa_avl_node_s *t = (*x)->left;

    (*x)->left = t->right;
    t->right = *x;

    qsa_avl_calculate_height(*x);
    qsa_avl_calculate_height(t);

    x = &t;
}

static void qsa_avl_turn_right(qsa_avl_node_s **x)
{
    qsa_avl_node_s *t = (*x)->right;

    (*x)->right = t->left;
    t->left = *x;

    qsa_avl_calculate_height(*x);
    qsa_avl_calculate_height(t);

    x = &t;
}

static void qsa_avl_balance(qsa_avl_node_s *x)
{
    int prev_height = x->height;

    int need_balance = 0;

    qsa_avl_calculate_height(x);

    int balance = qsa_avl_get_balance(x);

    if (balance > 1) {
        if (qsa_avl_get_balance(x->right) < 0) {
            qsa_avl_turn_left(&(x->right));
        }

        qsa_avl_turn_right(&x);

    } else if (balance < -1) {
        if (qsa_avl_get_balance(x->left) > 0) {
            qsa_avl_turn_right(&(x->left));
        }

        qsa_avl_turn_left(&x);
    }

    if (x->height == prev_height) {
        need_balance = 0;
    }
}
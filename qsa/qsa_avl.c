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

static void qsa_avl_turn_left(qsa_avl_node_s *x){
    
}
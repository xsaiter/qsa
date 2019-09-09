#include <assert.h>

#include "qsa_rbt.h"

static struct qsa_rbt_node *qsa_rbt_node_create(void *key,
                                                enum qsa_rbt_colors color) {
  struct qsa_rbt_node *r = qsa_malloc(sizeof(struct qsa_rbt_node));
  r->key = key;
  r->color = color;
  r->parent = r->left = r->right = NULL;
  return r;
}

struct qsa_rbt *qsa_rbt_create(size_t key_size, qsa_cmp_fn *key_cmp) {
  struct qsa_rbt *t = qsa_malloc(sizeof(struct qsa_rbt));

  t->key_size = key_size;
  t->key_cmp = key_cmp;
  t->root = NULL;

  struct qsa_rbt_node *nil = qsa_rbt_node_create(NULL, BLACK);
  nil->parent = t->root;

  t->root->parent = nil;
  t->nil = nil;

  return t;
}

struct qsa_rbt_node *qsa_rbt_search(const struct qsa_rbt *t, const void *key) {
  struct qsa_rbt_node *x = t->root;

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

static void qsa_rbt_left_rotate(struct qsa_rbt *t, struct qsa_rbt_node *x) {
  assert(x->right != t->nil);

  struct qsa_rbt_node *y = x->right;
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

static void qsa_rbt_right_rotate(struct qsa_rbt *t, struct qsa_rbt_node *x) {}

static void qsa_rbt_insert_restore(struct qsa_rbt *t, struct qsa_rbt_node *z) {
  struct qsa_rbt_node *y = NULL;

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

void qsa_rbt_insert(struct qsa_rbt *t, void *key) {
  int cmp = 0;

  struct qsa_rbt_node *z = qsa_rbt_node_create(key, RED);

  struct qsa_rbt_node *y = t->nil;
  struct qsa_rbt_node *x = t->root;

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

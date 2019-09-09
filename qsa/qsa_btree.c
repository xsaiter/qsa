#include <stdlib.h>

#include "qsa_btree.h"

struct qsa_btree *qsa_btree_create(size_t degree) {
  struct qsa_btree *t = qsa_malloc(sizeof(struct qsa_btree));
  t->degree = degree;
  t->max_ne = 2 * degree - 1;
  t->max_nc = t->max_ne + 1;
  t->root = NULL;
  return t;
}

void qsa_btree_free(struct qsa_btree *t) { free(t); }

static struct qsa_btree_node *qsa_btree_node_create(struct qsa_btree *t) {
  struct qsa_btree_node *x = qsa_malloc(sizeof(struct qsa_btree_node));

  x->n = 0;
  x->e = qsa_malloc(sizeof(struct qsa_btree_entry *) * t->max_ne);
  x->c = qsa_malloc(sizeof(struct qsa_btree_node *) * t->max_nc);
  x->is_leaf = false;

  return x;
}

void qsa_btree_node_split_child(struct qsa_btree *t, struct qsa_btree_node *x,
                                int i) {
  size_t d = t->degree;

  struct qsa_btree_node *y = x->c[i];

  struct qsa_btree_node *z = qsa_btree_node_create(t);

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

static bool qsa_btree_node_is_full(struct qsa_btree *t,
                                   struct qsa_btree_node *x) {
  return x->n == t->max_ne;
}

static struct qsa_btree_entry *qsa_btree_entry_create(int key, int ptr) {
  struct qsa_btree_entry *e = qsa_malloc(sizeof(struct qsa_btree_entry));
  e->key = key;
  e->ptr = ptr;
  return e;
}

static void qsa_btree_insert_non_full(struct qsa_btree *t,
                                      struct qsa_btree_node *x, int key,
                                      int ptr) {
  int i = x->n - 1;

  if (x->is_leaf) {
    struct qsa_btree_entry *e = qsa_btree_entry_create(key, ptr);

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

    struct qsa_btree_node *c = x->c[i];

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

void qsa_btree_insert(struct qsa_btree *t, int key, int ptr) {
  struct qsa_btree_node *r = t->root;

  bool is_full = qsa_btree_node_is_full(t, r);

  if (is_full) {
    struct qsa_btree_node *x = qsa_btree_node_create(t);

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

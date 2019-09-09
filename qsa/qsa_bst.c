#include <stdlib.h>
#include <string.h>

#include "qsa_bst.h"
#include "qsa_core.h"

struct qsa_bst *qsa_bst_create(size_t key_size, qsa_cmp_fn *key_cmp) {
  struct qsa_bst *t = qsa_malloc(sizeof(struct qsa_bst));
  t->key_size = key_size;
  t->key_cmp = key_cmp;
  return t;
}

static struct qsa_bst_node *qsa_bst_node_create(struct qsa_bst *t, void *key) {
  struct qsa_bst_node *node = qsa_malloc(sizeof(struct qsa_bst_node));

  node->key = qsa_malloc(t->key_size);
  memcpy(node->key, key, t->key_size);

  return node;
}

void qsa_bst_free(struct qsa_bst *t) { free(t); }

static void qsa_bst_add_node(struct qsa_bst *t, void *key,
                             struct qsa_bst_node *x) {
  if (t->key_cmp(x->key, key) == 0) {
    return;
  }

  if (t->key_cmp(x->key, key) > 0) {
    if (!x->left) {
      x->left = qsa_bst_node_create(t, key);
    } else {
      qsa_bst_add_node(t, key, x->left);
    }
  } else {
    if (!x->right) {
      x->right = qsa_bst_node_create(t, key);
    } else {
      qsa_bst_add_node(t, key, x->right);
    }
  }
}

void qsa_bst_insert(struct qsa_bst *t, void *key) {
  if (!t->root) {
    t->root = qsa_bst_node_create(t, key);
  } else {
    qsa_bst_add_node(t, key, t->root);
  }
}

struct qsa_bst_node *qsa_bst_search(const struct qsa_bst *t, const void *key) {
  struct qsa_bst_node *r = t->root;

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

static void qsa_bst_transplant(struct qsa_bst *t, struct qsa_bst_node *a,
                               struct qsa_bst_node *b) {
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

static struct qsa_bst_node *qsa_bst_min_node(struct qsa_bst_node *x) {
  struct qsa_bst_node *c = x;
  while ((c->left)) {
    c = c->left;
  }
  return c;
}

static void qsa_bst_remove_node(struct qsa_bst *t, struct qsa_bst_node *x) {
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
    qsa_bst_transplant(t, x, x->right);
  } else if (!x->right) {
    qsa_bst_transplant(t, x, x->left);
  } else {
    struct qsa_bst_node *m = qsa_bst_min_node(x->right);

    if (m->parent != x) {
      qsa_bst_transplant(t, m, m->right);
      m->right = x->right;
      m->right->parent = m;
    }

    qsa_bst_transplant(t, x, m);
    m->left = x->left;
    m->left->parent = m;
  }
}

static void qsa_bst_delete_node(struct qsa_bst *t, void *key,
                                struct qsa_bst_node *x) {
  if (x) {
    int cmp = t->key_cmp(x->key, key);

    if (cmp > 0) {
      qsa_bst_delete_node(t, key, x->left);
    } else if (cmp < 0) {
      qsa_bst_delete_node(t, key, x->right);
    } else {
      qsa_bst_remove_node(t, x);
    }
  }
}

void qsa_bst_delete(struct qsa_bst *t, void *key) {
  qsa_bst_delete_node(t, key, t->root);
}

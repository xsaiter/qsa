#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "qsa_avl.h"

#include "qsa_core.h"

typedef enum { ROTATE_LEFT, ROTATE_RIGHT } qsa_rotate_types_s;

qsa_avl_s *qsa_avl_create(size_t data_size, qsa_cmp_fn *cmp_data) {
  qsa_avl_s *t = qsa_malloc(sizeof(qsa_avl_s));

  t->data_size = data_size;
  t->root = NULL;
  t->cmp_data = cmp_data;

  return t;
}

static void qsa_avl_free_r(qsa_avl_node_s *x) {
  if (!x) {
    return;
  }

  qsa_avl_free_r(x->left);

  qsa_avl_free_r(x->right);

  free(x->data);
  free(x);
}

void qsa_avl_free(qsa_avl_s *t) {
  qsa_avl_free_r(t->root);
  free(t);
}

static void qsa_avl_set_height(qsa_avl_node_s *x) {
  int l = 0, r = 0;

  if (x->left) {
    l = x->left->height;
  }

  if (x->right) {
    r = x->right->height;
  }

  if (l > r) {
    x->height = l + 1;
  } else {
    x->height = r + 1;
  }
}

static int qsa_avl_get_balance(qsa_avl_node_s *x) {
  int l = 0, r = 0;

  if (x->left) {
    l = x->left->height;
  }

  if (x->right) {
    r = x->right->height;
  }

  return r - l;
}

static void qsa_avl_rotate(qsa_avl_node_s **x, qsa_rotate_types_s type) {
  qsa_avl_node_s *t;

  if (type == ROTATE_LEFT) {
    t = (*x)->left;
    (*x)->left = t->right;
    t->right = *x;
  } else {
    t = (*x)->right;
    (*x)->right = t->left;
    t->left = *x;
  }

  qsa_avl_set_height(*x);

  qsa_avl_set_height(t);

  *x = t;
}

static void qsa_avl_balance(qsa_avl_node_s **x) {
  qsa_avl_set_height(*x);

  int balance = qsa_avl_get_balance(*x);

  if (balance > 1) {
    if (qsa_avl_get_balance((*x)->right) < 0) {
      qsa_avl_rotate(&((*x)->right), ROTATE_LEFT);
    }

    qsa_avl_rotate(x, ROTATE_RIGHT);

  } else if (balance < -1) {
    if (qsa_avl_get_balance((*x)->left) > 0) {
      qsa_avl_rotate(&((*x)->left), ROTATE_RIGHT);
    }

    qsa_avl_rotate(x, ROTATE_LEFT);
  }
}

static qsa_avl_node_s *qsa_avl_node_new(qsa_avl_s *t, void *data) {
  qsa_avl_node_s *x = qsa_malloc(sizeof(qsa_avl_node_s));

  x->data = qsa_malloc(t->data_size);

  memcpy(x->data, data, t->data_size);

  x->left = x->right = NULL;

  x->height = 1;

  return x;
}

static void qsa_avl_insert_r(qsa_avl_s *t, qsa_avl_node_s **x, void *data) {
  if (!(*x)) {
    *x = qsa_avl_node_new(t, data);
    return;
  }

  int cmp = t->cmp_data((*x)->data, data);

  if (cmp > 0) {
    qsa_avl_insert_r(t, &((*x)->left), data);
    qsa_avl_balance(x);
  } else if (cmp < 0) {
    qsa_avl_insert_r(t, &((*x)->right), data);
    qsa_avl_balance(x);
  }
}

void qsa_avl_insert(qsa_avl_s *t, void *data) {
  qsa_avl_insert_r(t, &(t->root), data);
}

static qsa_avl_node_s *qsa_avl_search_r(qsa_avl_s *t, qsa_avl_node_s *x,
                                        void *data) {
  if (!x) {
    return NULL;
  }

  int cmp = t->cmp_data(x->data, data);

  if (cmp > 0) {
    return qsa_avl_search_r(t, x->left, data);
  }

  if (cmp < 0) {
    return qsa_avl_search_r(t, x->right, data);
  }

  return x;
}

qsa_avl_node_s *qsa_avl_search(qsa_avl_s *t, void *data) {
  return qsa_avl_search_r(t, t->root, data);
}

static void qsa_avl_print_r(qsa_avl_s *t, qsa_avl_node_s *x,
                            void (*display)(void *data), int depth) {
  if (!x) {
    return;
  }

  printf(" %d", depth);

  display(x->data);

  if (x->left) {
    printf("lhs:");
    display(x->left->data);
  }

  if (x->right) {
    printf("rhs:");
    display(x->right->data);
  }

  qsa_avl_print_r(t, x->left, display, depth + 1);

  qsa_avl_print_r(t, x->right, display, depth + 1);
}

void qsa_avl_print(qsa_avl_s *t, void (*display)(void *data)) {
  qsa_avl_print_r(t, t->root, display, 0);
}

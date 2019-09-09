#include <stdlib.h>
#include <string.h>

#include "qsa_dict.h"

#include "qsa_utils.h"

#define QSA_DICT_TABLE_SIZE (16)

struct qsa_dict *qsa_dict_create(size_t key_size, qsa_hash_fn *key_hash,
                                 qsa_eq_fn *key_eq, size_t value_size) {
  struct qsa_dict *d = qsa_malloc(sizeof(struct qsa_dict));

  d->key_size = key_size;
  d->key_hash = key_hash;
  d->key_equals = key_eq;

  d->value_size = value_size;

  d->table_size = QSA_DICT_TABLE_SIZE;

  d->table = qsa_malloc(d->table_size * sizeof(void *));
  for (int i = 0; i < d->table_size; ++i) {
    d->table[i] = NULL;
  }

  return d;
}

inline static unsigned int idx_table(struct qsa_dict *d, const void *key) {
  unsigned int h = d->key_hash(key);
  return h % d->table_size;
}

static struct qsa_dict_elem *q_find_elem(struct qsa_dict *d, const void *key) {
  struct qsa_dict_elem *e = d->table[idx_table(d, key)];
  while (e && !(d->key_equals(e->key, key))) {
    e = e->next;
  }
  return e;
}

static struct qsa_dict_elem *elem_new(struct qsa_dict *d, void *key,
                                      void *value) {
  struct qsa_dict_elem *e = qsa_malloc(sizeof(struct qsa_dict_elem));

  e->key = qsa_malloc(d->key_size);
  memcpy(e->key, key, d->key_size);

  e->value = qsa_malloc(d->value_size);
  memcpy(e->value, value, d->value_size);

  e->hash = d->key_hash(key);
  e->next = NULL;

  return e;
}

void qsa_dict_free(struct qsa_dict *d) { free(d); }

void qsa_dict_add(struct qsa_dict *d, void *key, void *value) {
  unsigned int idx = idx_table(d, key);
  struct qsa_dict_elem *e = d->table[idx];
  if (!e) {
    d->table[idx] = elem_new(d, key, value);
  } else {
    struct qsa_dict_elem *x = e;
    while (x && !(d->key_equals(e->key, key))) {
      x = x->next;
    }

    if (!x) {
      struct qsa_dict_elem *s = elem_new(d, key, value);
      s->next = d->table[idx];
      d->table[idx] = s;
    }
  }
}

void *qsa_dict_get(struct qsa_dict *d, const void *key) {
  struct qsa_dict_elem *e = q_find_elem(d, key);
  if (e) {
    return e->value;
  }
  return NULL;
}

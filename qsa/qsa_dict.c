#include <stdlib.h>
#include <string.h>

#include "qsa_dict.h"

#include "qsa_utils.h"

#define QSA_DICT_TABLE_SIZE (16)

qsa_dict_s *qsa_dict_create(size_t key_size, qsa_hash_fn *key_hash,
                            qsa_eq_fn *key_eq, size_t value_size) {
  qsa_dict_s *d = qsa_malloc(sizeof(qsa_dict_s));

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

inline static unsigned int idx_table(qsa_dict_s *d, const void *key) {
  unsigned int h = d->key_hash(key);
  return h % d->table_size;
}

static qsa_dict_elem_s *q_find_elem(qsa_dict_s *d, const void *key) {
  qsa_dict_elem_s *e = d->table[idx_table(d, key)];
  while (e && !(d->key_equals(e->key, key))) {
    e = e->next;
  }
  return e;
}

static qsa_dict_elem_s *elem_new(qsa_dict_s *d, void *key, void *value) {
  qsa_dict_elem_s *e = qsa_malloc(sizeof(qsa_dict_elem_s));

  e->key = qsa_malloc(d->key_size);
  memcpy(e->key, key, d->key_size);

  e->value = qsa_malloc(d->value_size);
  memcpy(e->value, value, d->value_size);

  e->hash = d->key_hash(key);
  e->next = NULL;

  return e;
}

void qsa_dict_free(qsa_dict_s *d) { free(d); }

void qsa_dict_add(qsa_dict_s *d, void *key, void *value) {
  unsigned int idx = idx_table(d, key);
  qsa_dict_elem_s *e = d->table[idx];
  if (!e) {
    d->table[idx] = elem_new(d, key, value);
  } else {
    qsa_dict_elem_s *x = e;
    while (x && !(d->key_equals(e->key, key))) {
      x = x->next;
    }

    if (!x) {
      qsa_dict_elem_s *s = elem_new(d, key, value);
      s->next = d->table[idx];
      d->table[idx] = s;
    }
  }
}

void *qsa_dict_get(qsa_dict_s *d, const void *key) {
  qsa_dict_elem_s *e = q_find_elem(d, key);
  if (e) {
    return e->value;
  }
  return NULL;
}

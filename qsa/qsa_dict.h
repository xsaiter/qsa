#ifndef QSA_DICT_H
#define QSA_DICT_H

#include "qsa_core.h"

extern void *dict_not_found;

struct qsa_dict_elem {
  void *key;
  void *value;
  struct qsa_dict_elem *next;
  unsigned int hash;
};

struct qsa_dict {
  int table_size;
  struct qsa_dict_elem **table;
  qsa_hash_fn *key_hash;
  qsa_eq_fn *key_equals;
  size_t key_size;
  size_t value_size;
};

struct qsa_dict *qsa_dict_create(size_t key_size, qsa_hash_fn *key_hash,
                                 qsa_eq_fn *key_eq, size_t value_size);

void qsa_dict_free(struct qsa_dict *d);

void qsa_dict_add(struct qsa_dict *d, void *key, void *value);

void *qsa_dict_get(struct qsa_dict *d, const void *key);

#endif /* QSA_DICT_H */

#ifndef QSA_DICT_H
#define QSA_DICT_H

#include "qsa_core.h"

extern void *dict_not_found;

typedef struct qsa_dict_elem_s {
    void *key;
    void *value;
    struct qsa_dict_elem_s *next;
    unsigned int hash;
} qsa_dict_elem_s;

typedef struct {
    int table_size;
    qsa_dict_elem_s **table;
    qsa_hash_fn *key_hash;
    qsa_equals_fn *key_equals;
    size_t key_size;
    size_t value_size;
} qsa_dict_s;

qsa_dict_s *qsa_dict_new(size_t key_size, qsa_hash_fn *key_hash, qsa_equals_fn *key_equals, size_t value_size);
void qsa_dict_free(qsa_dict_s *d);
void qsa_dict_add(qsa_dict_s *d, void *key, void *value);
void *qsa_dict_get(qsa_dict_s *d, const void *key);

#endif /* QSA_DICT_H */
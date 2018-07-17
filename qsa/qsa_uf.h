/*
 * union-find data structure (disjoint sets)
 */

#ifndef QSA_UF_H
#define QSA_UF_H

#include <stddef.h>

typedef struct {
    int *p;
    int *s;
    size_t n;
} qsa_uf_s;

qsa_uf_s* qsa_uf_create(size_t n);

void qsa_uf_free(qsa_uf_s *uf);

int qsa_uf_find(qsa_uf_s *uf, int v);

void qsa_uf_union(qsa_uf_s *uf, int v1, int v2);

#endif /* QSA_UF_H */
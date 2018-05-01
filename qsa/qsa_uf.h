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
} q_uf_s;

q_uf_s* q_uf_new(size_t n);

void q_uf_free(q_uf_s *uf);

int q_uf_find(q_uf_s *uf, int v);

void q_uf_union(q_uf_s *uf, int v1, int v2);

#endif /* QSA_UF_H */
/*
 * union-find data structure (disjoint sets)
 */

#ifndef QSA_UF_H
#define QSA_UF_H

#include <stddef.h>

struct qsa_uf {
  int *p;
  int *s;
  size_t n;
};

struct qsa_uf *qsa_uf_create(size_t n);

void qsa_uf_free(struct qsa_uf *uf);

int qsa_uf_find(struct qsa_uf *uf, int v);

void qsa_uf_union(struct qsa_uf *uf, int v1, int v2);

#endif /* QSA_UF_H */

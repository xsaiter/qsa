#include <stdlib.h>

#include "qsa_uf.h"
#include "qsa_core.h"

q_uf_s* q_uf_new(size_t n)
{
    q_uf_s *uf = qsa_malloc(sizeof (q_uf_s));

    uf->n = n;
    uf->s = qsa_malloc(n * sizeof (int));
    uf->p = qsa_malloc(n * sizeof (int));

    for (size_t i = 0; i < n; ++i) {
        uf->p[i] = i;
        uf->s[i] = 1;
    }

    return uf;
}

void q_uf_free(q_uf_s *uf)
{
    free(uf->s);
    free(uf->p);
    free(uf);
}

int q_uf_find(q_uf_s *uf, int v)
{
    if (uf->p[v] == v) {
        return v;
    }
    return q_uf_find(uf, uf->p[v]);
}

void q_uf_union(q_uf_s *uf, int v1, int v2)
{
    int r1 = q_uf_find(uf, v1);
    int r2 = q_uf_find(uf, v2);

    if (v1 == v2) {
        return;
    }

    if (uf->s[r1] > uf->s[r2]) {
        uf->s[r1] += uf->p[r2];
        uf->p[r2] = r1;
    } else {
        uf->s[r2] += uf->s[r1];
        uf->p[r1] = r2;
    }
}
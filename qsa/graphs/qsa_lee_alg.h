#ifndef QSA_LEE_ALG_H
#define QSA_LEE_ALG_H

#include <stdbool.h>

#include "../qsa_vector.h"

struct qsa_lee_cell {
  int n;
  int x, y;
  bool visited;
};

struct qsa_lee_opts {
  int **a;
  int rows, cols;
  int beg_x, beg_y;
  int end_x, end_y;
};

bool qsa_lee_alg(struct qsa_lee_opts *opts, struct qsa_vector *result);

#endif /* QSA_LEE_ALG_H */

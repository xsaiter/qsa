#ifndef QSA_LEE_ALG_H
#define QSA_LEE_ALG_H

#include <stdbool.h>

#include "../qsa_vector.h"

typedef struct {
  int n;
  int x, y;
  bool visited;
} qsa_lee_cell_s;

typedef struct {
  int **a;
  int rows, cols;
  int beg_x, beg_y;
  int end_x, end_y;
} qsa_lee_opts_s;

bool qsa_lee_alg(qsa_lee_opts_s *opts, qsa_vector_s *result);

#endif /* QSA_LEE_ALG_H */

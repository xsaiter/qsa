#ifndef QSA_LEE_ALG_H
#define QSA_LEE_ALG_H

#include <stdbool.h>

#include "../qsa_vector.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int n;
        int x, y;
        bool visited;
    } q_lee_cell;

    typedef struct {
        int **a;
        int rows, cols;
        int beg_x, beg_y;
        int end_x, end_y;
    } q_lee_opts;

    bool q_lee_alg(q_lee_opts *opts, q_vector *result);

#ifdef __cplusplus
}
#endif

#endif /* QSA_LEE_ALG_H */


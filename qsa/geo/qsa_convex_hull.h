#ifndef QSA_CONVEX_HULL_H
#define QSA_CONVEX_HULL_H

#include "../qsa_stack.h"
#include "qsa_geo.h"

void qsa_graham_scan(struct qsa_point *points, int npoints,
                     struct qsa_stack *hull);

#endif /* QSA_CONVEX_HULL_H */

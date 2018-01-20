#ifndef QSA_CONVEX_HULL_H
#define QSA_CONVEX_HULL_H

#include "qsa_geo.h"
#include "../qsa_stack.h"

void qsa_graham_scan(qsa_point_s *points, int npoints, qsa_stack_s* hull);

#endif /* QSA_CONVEX_HULL_H */


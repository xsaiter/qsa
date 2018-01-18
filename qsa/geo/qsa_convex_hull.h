#ifndef QSA_CONVEX_HULL_H
#define QSA_CONVEX_HULL_H

#include "qsa_geo.h"
#include "../qsa_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

    void qsa_graham_scan(qsa_point_s *points, int npoints, qsa_stack_s* hull);

#ifdef __cplusplus
}
#endif

#endif /* QSA_CONVEX_HULL_H */


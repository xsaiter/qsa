#ifndef _QSA_CONVEX_HULL_H
#define _QSA_CONVEX_HULL_H

#include "qsa_geo.h"
#include "../qsa_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

    void q_graham_scan(q_point *points, int npoints, q_stack* hull);

#ifdef __cplusplus
}
#endif

#endif /* _QSA_CONVEX_HULL_H */


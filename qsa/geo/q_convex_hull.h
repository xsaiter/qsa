#ifndef Q_CONVEX_HULL_H
#define Q_CONVEX_HULL_H

#include "q_geo.h"
#include "../q_stack.h"

#ifdef __cplusplus
extern "C" {
#endif

    void q_graham_scan(q_point *points, int npoints, q_stack* hull);

#ifdef __cplusplus
}
#endif

#endif /* Q_CONVEX_HULL_H */


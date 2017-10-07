#define _GNU_SOURCE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "q_convex_hull.h"

#define Q_MIN_POINTS 3

static int q_smaller_angle(const void *x1, const void *x2, void *xpivot)
{
    q_point *p1 = (q_point*) x1;
    q_point *p2 = (q_point*) x2;
    q_point *pivot = (q_point*) xpivot;

    int r = q_rotate(pivot, p1, p2);
    if (r == 0) {
        int d1 = q_distance2(pivot, p1);
        int d2 = q_distance2(pivot, p2);
        return (d1 > d2);
    }

    return (r < 0);
}

void q_graham_scan(q_point *points, int npoints, q_stack *hull)
{
    if (npoints <= Q_MIN_POINTS) {
        for (int i = 0; i < npoints; i++) {
            q_stack_push(hull, &points[i]);
        }
        return;
    }

    int ymin;
    int ymin_i = 0;
    ymin = points[0].y;
    for (int i = 0; i < npoints; i++) {
        if (points[i].y < ymin) {
            ymin = points[i].y;
            ymin_i = i;
        }
    }
    
    q_point t = points[0];
    points[0] = points[ymin_i];
    points[ymin_i] = t;

    qsort_r(&points[1], npoints - 1, sizeof (q_point), q_smaller_angle, &points[0]);

    q_stack_push(hull, &points[0]);
    q_stack_push(hull, &points[1]);
    q_stack_push(hull, &points[2]);

    for (int i = Q_MIN_POINTS; i < npoints; i++) {
        while (true) {
            q_point *p1 = q_stack_pop(hull);
            q_point *p2 = q_stack_pop(hull);

            q_stack_push(hull, p2);
            q_stack_push(hull, p1);

            if (q_rotate(p2, p1, &points[i]) == -1) {
                q_stack_pop(hull);
            } else {
                q_stack_push(hull, &points[i]);
                break;
            }
        }
    }
}


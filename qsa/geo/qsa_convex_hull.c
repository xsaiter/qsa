//#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "qsa_convex_hull.h"

#define QSA_CONVEX_HULL_MIN_POINTS 3

static int qsa_smaller_angle(const void *x1, const void *x2, void *xpivot) {
  qsa_point_s *p1 = (qsa_point_s *)x1;
  qsa_point_s *p2 = (qsa_point_s *)x2;
  qsa_point_s *pivot = (qsa_point_s *)xpivot;

  int r = qsa_rotate(pivot, p1, p2);
  if (r == 0) {
    int d1 = qsa_distance2(pivot, p1);
    int d2 = qsa_distance2(pivot, p2);
    return (d1 > d2);
  }

  return (r < 0);
}

void qsa_graham_scan(qsa_point_s *points, int npoints, qsa_stack_s *hull) {
  if (npoints <= QSA_CONVEX_HULL_MIN_POINTS) {
    for (int i = 0; i < npoints; i++) {
      qsa_stack_push(hull, &points[i]);
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

  qsa_point_s t = points[0];
  points[0] = points[ymin_i];
  points[ymin_i] = t;

  qsort_r(&points[1], npoints - 1, sizeof(qsa_point_s), qsa_smaller_angle,
          &points[0]);

  qsa_stack_push(hull, &points[0]);
  qsa_stack_push(hull, &points[1]);
  qsa_stack_push(hull, &points[2]);

  for (int i = QSA_CONVEX_HULL_MIN_POINTS; i < npoints; i++) {
    while (true) {
      qsa_point_s *p1 = qsa_stack_pop(hull);
      qsa_point_s *p2 = qsa_stack_pop(hull);

      qsa_stack_push(hull, p2);
      qsa_stack_push(hull, p1);

      if (qsa_rotate(p2, p1, &points[i]) == -1) {
        qsa_stack_pop(hull);
      } else {
        qsa_stack_push(hull, &points[i]);
        break;
      }
    }
  }
}

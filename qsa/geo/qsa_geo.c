#include "qsa_geo.h"

double qsa_cross_product(const struct qsa_point *a, const struct qsa_point *b,
                         const struct qsa_point *c) {
  return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

/*
 * > 0 if a, b, c - clockwise
 * < 0 - counterclockwise
 * = 0 - collinear
 */
int qsa_rotate(const struct qsa_point *a, const struct qsa_point *b,
               const struct qsa_point *c) {
  double s = qsa_cross_product(a, b, c);

  if (s < 0.0) {
    return (-1);
  }
  if (s > 0.0) {
    return 1;
  }
  return 0;
}

double qsa_distance2(const struct qsa_point *a, const struct qsa_point *b) {
  double dx = a->x - b->x;
  double dy = a->y - b->y;
  return dx * dx + dy * dy;
}

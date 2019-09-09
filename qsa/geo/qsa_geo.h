#ifndef QSA_GEO_H
#define QSA_GEO_H

struct qsa_point {
  double x, y;
};

double qsa_cross_product(const struct qsa_point *a, const struct qsa_point *b,
                         const struct qsa_point *c);

int qsa_rotate(const struct qsa_point *a, const struct qsa_point *b,
               const struct qsa_point *c);

double qsa_distance2(const struct qsa_point *a, const struct qsa_point *b);

#endif /* QSA_GEO_H */

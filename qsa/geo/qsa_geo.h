#ifndef QSA_GEO_H
#define QSA_GEO_H

typedef struct {
    double x, y;
} qsa_point_s;

double qsa_cross_product(const qsa_point_s *a, const qsa_point_s *b, const qsa_point_s *c);
int qsa_rotate(const qsa_point_s *a, const qsa_point_s *b, const qsa_point_s *c);
double qsa_distance2(const qsa_point_s *a, const qsa_point_s *b);

#endif /* QSA_GEO_H */
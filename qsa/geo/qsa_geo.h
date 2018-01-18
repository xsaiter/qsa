#ifndef QSA_GEO_H
#define QSA_GEO_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        double x, y;
    } qsa_point_s;

    int qsa_rotate(const qsa_point_s *a, const qsa_point_s *b, const qsa_point_s *c);
    double qsa_distance2(const qsa_point_s *a, const qsa_point_s *b);

#ifdef __cplusplus
}
#endif

#endif /* QSA_GEO_H */
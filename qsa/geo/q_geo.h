#ifndef Q_GEO_H
#define Q_GEO_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        double x, y;
    } q_point;

    int q_rotate(const q_point *a, const q_point *b, const q_point *c);
    double q_distance2(const q_point *a, const q_point *b);


#ifdef __cplusplus
}
#endif

#endif /* Q_GEO_H */
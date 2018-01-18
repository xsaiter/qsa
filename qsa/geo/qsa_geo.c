#include "qsa_geo.h"

/* 
 * > 0 if a, b, c - clockwise
 * < 0 - counterclockwise 
 * = 0 - collinear    
 */
int qsa_rotate(const qsa_point_s *a, const qsa_point_s *b, const qsa_point_s *c)
{
    double s = (b->x - a->x)*(c->y - a->y) - (b->y - a->y)*(c->x - a->x);

    if (s == 0.0) {
        return (0);
    }

    if (s < 0.0) {
        return (-1);
    }

    return (1);
}

double qsa_distance2(const qsa_point_s *a, const qsa_point_s *b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;    
    return dx * dx + dy*dy;
}
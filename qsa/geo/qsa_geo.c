#include "qsa_geo.h"

/* 
 * > 0 if a, b, c - clockwise
 * < 0 - counterclockwise 
 * = 0 - collinear    
 */
int q_rotate(const q_point *a, const q_point *b, const q_point *c)
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

double q_distance2(const q_point *a, const q_point *b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;    
    return dx * dx + dy*dy;
}
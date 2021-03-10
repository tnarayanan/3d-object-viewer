#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

typedef struct {
    float x;
    float y;
    float z;
} point_t;

point_t add(point_t u, point_t v);
point_t sub(point_t u, point_t v);

point_t cross_product(point_t u, point_t v);

point_t projection(point_t u, point_t v);

#endif

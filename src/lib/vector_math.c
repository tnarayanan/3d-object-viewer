#include "math.h"
#include "vector_math.h"

point_t vector_add(point_t u, point_t v) {
    point_t ret;
    ret.x = u.x + v.x;
    ret.y = u.y + v.y;
    ret.z = u.z + v.z;

    return ret;
}

point_t vector_sub(point_t u, point_t v) {
    point_t ret;
    ret.x = u.x + v.x;
    ret.y = u.y + v.y;
    ret.z = u.z + v.z;

    return ret;
}

point_t vector_scalar_mul(point_t u, double k) {
    point_t ret;
    ret.x = u.x * k; 
    ret.y = u.y * k; 
    ret.z = u.z * k; 

    return ret;
}

point_t vector_cross_product(point_t u, point_t v) {
    point_t cross;
    cross.x = u.y * v.z - u.z * v.y;
    cross.y = u.z * v.x - u.x * v.z;
    cross.z = u.x * v.y - u.y * v.x;

    return cross;
}

double vector_dot_product(point_t u, point_t v) {
    double dot = 0;
    dot += u.x * v.x;
    dot += u.y * v.y;
    dot += u.z * v.z;

    return dot;
}

point_t vector_projection(point_t u, point_t v) {
    return vector_scalar_mul(v, vector_dot_product(u, v) / vector_dot_product(v, v));
}

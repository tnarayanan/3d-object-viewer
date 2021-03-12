#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

/*
 * This module provides functions for basic vector math operations
 * including add/subtract, scalar multiplication, dot/cross products,
 * and projections.
 *
 * Author: Tejas Narayanan <tejasn100@gmail.com>
 * Date: Mar 11 2021
 */

typedef struct {
    float x;
    float y;
    float z;
} point_t;

point_t vector_add(point_t u, point_t v);

point_t vector_sub(point_t u, point_t v);

point_t vector_scalar_mul(point_t u, double k);

point_t vector_cross_product(point_t u, point_t v);

double vector_dot_product(point_t u, point_t v);

point_t vector_projection(point_t u, point_t v);

#endif

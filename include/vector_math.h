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

/*typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec_4_t;

typedef struct {
	vec_4_t col1;
	vec_4_t col2;
	vec_4_t col3;
	vec_4_t col4;
} matrix_4_t;*/

typedef struct {
	float m[4][4];
} matrix_4_t;

point_t vector_add(point_t u, point_t v);

point_t vector_sub(point_t u, point_t v);

point_t vector_scalar_mul(point_t u, float k);

point_t vector_cross_product(point_t u, point_t v);

float vector_dot_product(point_t u, point_t v);

point_t vector_projection(point_t u, point_t v);

float vector_magnitude(point_t u);

//matrix_4_t matrix_inverse(matrix_4_t m);

matrix_4_t matmul_matrix_4_by_matrix_4(matrix_4_t m1, matrix_4_t m2);

point_t matmul_point_by_matrix_4(point_t p, matrix_4_t m);

#endif

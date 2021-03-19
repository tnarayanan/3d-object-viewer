#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector_math.h"

matrix_4_t transform_reset_position(matrix_4_t mat);
matrix_4_t transform_reset_rotation(matrix_4_t mat);

matrix_4_t transform_set_position(matrix_4_t mat, float x, float y, float z);

matrix_4_t transform_rotate_x(matrix_4_t mat, float theta);
matrix_4_t transform_rotate_y(matrix_4_t mat, float theta);
matrix_4_t transform_rotate_z(matrix_4_t mat, float theta);

#endif

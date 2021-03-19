#include "transform.h"
#include "math.h"

matrix_4_t transform_reset_position(matrix_4_t mat) {
    mat.m[0][3] = 0;
    mat.m[1][3] = 0;
    mat.m[2][3] = 0;
    mat.m[3][3] = 1;

    return mat;
}

matrix_4_t transform_reset_rotation(matrix_4_t mat) {
    mat.m[0][0] = 1;
    mat.m[1][0] = 0;
    mat.m[2][0] = 0;

    mat.m[0][1] = 0;
    mat.m[1][1] = 1;
    mat.m[2][1] = 0;

    mat.m[0][2] = 0;
    mat.m[1][2] = 0;
    mat.m[2][2] = 1;

    return mat;
}

matrix_4_t transform_set_position(matrix_4_t mat, double x, double y, double z) {
    mat.m[0][3] = x;
    mat.m[1][3] = y;
    mat.m[2][3] = z;
    mat.m[3][3] = 1;

    return mat;
}

static matrix_4_t mat_from_arr(double arr[16]) {
    matrix_4_t mat;

    mat.m[0][0] = arr[0];
    mat.m[1][0] = arr[1];
    mat.m[2][0] = arr[2];
    mat.m[3][0] = arr[3];

    mat.m[0][1] = arr[4];
    mat.m[1][1] = arr[5];
    mat.m[2][1] = arr[6];
    mat.m[3][1] = arr[7];

    mat.m[0][2] = arr[8];
    mat.m[1][2] = arr[9];
    mat.m[2][2] = arr[10];
    mat.m[3][2] = arr[11];

    mat.m[0][3] = arr[12];
    mat.m[1][3] = arr[13];
    mat.m[2][3] = arr[14];
    mat.m[3][3] = arr[15];

    return mat;
}

matrix_4_t transform_rotate_x(matrix_4_t mat, double theta) {
    double orig_x = mat.m[0][3];
    double orig_y = mat.m[1][3];
    double orig_z = mat.m[2][3];

    double arr[16] = {1, 0, 0, 0,
                      0, cos(theta), sin(theta), 0,
                      0, -sin(theta), cos(theta), 0,
                      0, 0, 0, 1};
    matrix_4_t x_rot = mat_from_arr(arr);

    matrix_4_t result = matmul_matrix_4_by_matrix_4(mat, x_rot);
    result.m[0][3] = orig_x;
    result.m[1][3] = orig_y;
    result.m[2][3] = orig_z;

    return result;
}

matrix_4_t transform_rotate_y(matrix_4_t mat, double theta) {
    double orig_x = mat.m[0][3];
    double orig_y = mat.m[1][3];
    double orig_z = mat.m[2][3];

    double arr[16] = {cos(theta), 0, -sin(theta), 0,
                      0, 1, 0, 0,
                      sin(theta), 0, cos(theta), 0,
                      0, 0, 0, 1};
    matrix_4_t y_rot = mat_from_arr(arr);

    matrix_4_t result = matmul_matrix_4_by_matrix_4(mat, y_rot);
    result.m[0][3] = orig_x;
    result.m[1][3] = orig_y;
    result.m[2][3] = orig_z;

    return result;
}
matrix_4_t transform_rotate_z(matrix_4_t mat, double theta) {
    double orig_x = mat.m[0][3];
    double orig_y = mat.m[1][3];
    double orig_z = mat.m[2][3];

    double arr[16] = {cos(theta), sin(theta), 0, 0,
                      -sin(theta), cos(theta), 0, 0,
                      0, 0, 1, 0,
                      0, 0, 0, 1};
    matrix_4_t z_rot = mat_from_arr(arr);

    matrix_4_t result = matmul_matrix_4_by_matrix_4(mat, z_rot);
    result.m[0][3] = orig_x;
    result.m[1][3] = orig_y;
    result.m[2][3] = orig_z;

    return result;
}

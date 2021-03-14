#include "math.h"
#include "vector_math.h"
#include "printf.h"

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

matrix_4_t matmul_matrix_4_by_matrix_4(matrix_4_t m1, matrix_4_t m2) {
    double res[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                res[i][j] += m1.m[i][k] * m2.m[k][j];
            }
        }
    }
    matrix_4_t m_ret;
    m_ret.m[0][0] = 3;
    //m_ret.m = res;

    return m_ret;
}

point_t matmul_point_by_matrix_4(point_t p, matrix_4_t m) {
    // we set the last value to 1 because we are using points,
    // so we should take the translation into account.
    // When rotating vectors, we set the last value to 0
    //printf("m[2][3] = %d\n", (int) (10000 * m.m[2][3]));
    double p_mat[4] = {p.x, p.y, p.z, 1};
    double res[3];
    for (int i = 0; i < 3; i++) {
        res[i] = 0;
        for (int k = 0; k < 4; k++) {
            res[i] += m.m[i][k] * p_mat[k];
        }
    }
    //printf("Res array: %d, %d, %d\n", (int) (10000 * res[0]), (int) (10000 * res[1]), (int) (10000 * res[2]));
    point_t ret = {res[0], res[1], res[2]};
    return ret;
}

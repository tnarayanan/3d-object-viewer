#include "uart.h"
#include "printf.h"
#include "obj_parser.h"
#include "gl.h"
#include "gl_3d.h"
#include "vector_math.h"
#include "math.h"
#include "malloc.h"

matrix_4_t *mat_from_arr(double arr[16]) {
    matrix_4_t *mat = malloc(sizeof(matrix_4_t));

    mat->m[0][0] = arr[0];
    mat->m[1][0] = arr[1];
    mat->m[2][0] = arr[2];
    mat->m[3][0] = arr[3];

    mat->m[0][1] = arr[4];
    mat->m[1][1] = arr[5];
    mat->m[2][1] = arr[6];
    mat->m[3][1] = arr[7];

    mat->m[0][2] = arr[8];
    mat->m[1][2] = arr[9];
    mat->m[2][2] = arr[10];
    mat->m[3][2] = arr[11];

    mat->m[0][3] = arr[12];
    mat->m[1][3] = arr[13];
    mat->m[2][3] = arr[14];
    mat->m[3][3] = arr[15];

    return mat;
}

void main(void) {
    uart_init();
    gl_init(640, 512, GL_SINGLEBUFFER);
    gl_3d_init();
    obj_model_init();

    gl_3d_clear(GL_BLACK);

    obj_model_t *cube = obj_model_load("cube.obj");
    color_t colors[6] = {GL_MAGENTA, GL_BLUE, GL_AMBER, GL_MOSS, GL_CYAN, GL_RED};

    /*double arr[16] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      1, 1, -5, 1};*/
    double theta = PI/6;
    double arr[16] = {cos(theta), 0, -sin(theta), 0,
                      0, 1, 0, 0,
                      sin(theta), 0, cos(theta), 0,
                      1, 1, -5, 1};
    matrix_4_t *cam = mat_from_arr(arr);

    printf("About to draw triangles\n");
    for (int i = 0; i < cube->num_faces; i++) {
        gl_3d_draw_triangle(
                *(cube->faces[i].v1),
                *(cube->faces[i].v2),
                *(cube->faces[i].v3),
                *cam, 
                *cam,
                colors[i % 6]);
        printf("Drew triangle #%d\n", i);
    }
    printf("Drew all triangles\n");
    
    uart_putchar(EOT);
}

#include "timer.h"
#include "printf.h"
#include "gl_3d.h"
#include "math.h"
#include "assert.h"
#include "malloc.h"
#include "uart.h"

void test_gl_3d_clear(void){
    gl_3d_clear(GL_BLUE);
    timer_delay(1);
    gl_3d_clear(GL_WHITE);
    timer_delay(1);
    gl_3d_clear(GL_BLACK);
    timer_delay(1);
}

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

void test_gl_3d_draw_triangle(void){
    gl_3d_clear(GL_BLACK);

    point_t v1 = {.x = 10, .y = 10, .z = 1};
    //gl_draw_pixel(v1.x, v1.y, GL_CYAN);

    point_t v2 = {.x = 10, .y = 200, .z = 1};
    //gl_draw_pixel(v2.x, v2.y, GL_CYAN);

    point_t v3 = {.x = 100, .y = 100, .z = 1};
    //gl_draw_pixel(v3.x, v3.y, GL_CYAN);
    
    color_t colors[6] = {GL_MAGENTA, GL_BLUE, GL_AMBER, GL_MOSS, GL_CYAN, GL_RED};
    //for(int i = 0; i < (sizeof(colors)/4); i++){
        //gl_3d_draw_triangle(v1, v2, v3, v1, v2, colors[i]);
        //v1.x += 50;
        //v2.x += 50;
        //v3.x += 50;
    //}

    v1 = (point_t) {.x = 250, .y = 350, .z = 1};
    v2 = (point_t) {.x = 200, .y = 400, .z = 1};
    v3 = (point_t) {.x = 300, .y = 400, .z = 1};

    double arr[16] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      250, 375, -10, 1};
    matrix_4_t *cam = mat_from_arr(arr);
    
    for (int i = 0; i < (sizeof(colors)/4); i++) {
        gl_3d_draw_triangle(v1, v2, v3, *cam, *cam, colors[i]);
        double diff = 10;
        v1.z += diff;
        v2.z += diff;
        v3.z += diff;
        //arr[14] -= 10;
        cam = mat_from_arr(arr);
    }
}

void test_gl_3d_view_matrix(void) {
    point_t v1 = {0, 50, 30};
    point_t v2 = {100, 100, 10};
    point_t v3 = {150, 0, 10};

    double arr[16] = {1, 0, 0, 0,
                      0, 1, 0, 0,
                      0, 0, 1, 0,
                      0, 0, -10, 1};
    matrix_4_t *cam = mat_from_arr(arr);
    
    gl_3d_draw_triangle(v1, v2, v3, *cam, *cam, GL_RED);
}

/*void test_gl_3d_transformed_triangle(void) {
    point_t v1 = {0, 5, 0};
    point_t v2 = {10, 10, 0};
    point_t v3 = {15, 0, 0};

    double y_rot = -PI/6.0;
    matrix_4_t cam;
    cam.m = {cos(y_rot), 0, sin(y_rot), 10,
                    0, 1, 0, 5,
                    -sin(y_rot), 0, cos(y_rot), -20,
                    0, 0, 0, 1};

    gl_3d_draw_triangle(v1, v2, v3, cam, cam, GL_RED);

}*/

void main(void) {
    const int WIDTH = 640;
    const int HEIGHT = 512;

    gl_init(WIDTH, HEIGHT, GL_SINGLEBUFFER);
    gl_3d_init();

    printf("Running gl tests...\n");

    //test_gl_3d_clear();
    test_gl_3d_draw_triangle();
    //test_gl_3d_view_matrix();
    //test_gl_3d_transformed_triangle();

    printf("Finished running gl tests\n");
    uart_putchar(EOT);
} 


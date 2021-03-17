#include "gl_3d.h"
#include "malloc.h"
#include "printf.h"

#define INFINITY 0xffffffff
#define GLOBAL_WIDTH 4
#define GLOBAL_HEIGHT 3

static unsigned int *z_buf;

static void clear_z_buf() {
    int size = gl_get_width() * gl_get_height();
    for(int i = 0; i < size; i++){
        z_buf[i] = INFINITY; 
    }
}

void gl_3d_init(void) {
    z_buf = malloc(sizeof(unsigned int) * gl_get_width() * gl_get_height());    
}

static int edge(point_t v1, point_t v2, point_t p){
    return ((p.x - v1.x) * (v2.y - v1.y) - (p.y - v1.y) * (v2.x - v1.x) >= 0);
}


static double max(double a, double b, double c){
    double max = a;
    if(b > max) max = b;
    if(c > max) max = c;
    return max;
}

static double min(double a, double b, double c){
    double min = a;
    if(b < min) min = b;
    if(c < min) min = c;
    return min;
}

static void print_point(point_t v) {
    printf("Point: {%d, %d, %d}\n", (int) (10000 * v.x), (int) (10000 * v.y), (int) (10000 * v.z));
}

static point_t convert_to_pixels(point_t p) {
    int width = gl_get_width();
    int height = gl_get_height();
    int new_x_coord = p.x * width / ((double) GLOBAL_WIDTH);
    int new_y_coord = p.y * height / ((double) GLOBAL_HEIGHT);

    return (point_t) {new_x_coord, new_y_coord, p.z};
}

void gl_3d_draw_triangle(point_t v1, point_t v2, point_t v3, matrix_4_t cam, matrix_4_t light, color_t c) {

    // https://www.3dgep.com/understanding-the-view-matrix/#Look_At_Camera

    matrix_4_t view;
    view.m[0][0] = cam.m[0][0];
    view.m[1][0] = cam.m[0][1];
    view.m[2][0] = cam.m[0][2];
    view.m[3][0] = 0;

    view.m[0][1] = cam.m[1][0];
    view.m[1][1] = cam.m[1][1];
    view.m[2][1] = cam.m[1][2];
    view.m[3][1] = 0;
                          
    view.m[0][2] = cam.m[2][0];
    view.m[1][2] = cam.m[2][1];
    view.m[2][2] = cam.m[2][2];
    view.m[3][2] = 0;

    point_t cam_x = {cam.m[0][0], cam.m[1][0], cam.m[2][0]};
    point_t cam_y = {cam.m[0][1], cam.m[1][1], cam.m[2][1]};
    point_t cam_z = {cam.m[0][2], cam.m[1][2], cam.m[2][2]};
    point_t cam_eye = {cam.m[0][3], cam.m[1][3], cam.m[2][3]};
                          
    view.m[0][3] = -vector_dot_product(cam_x, cam_eye);
    view.m[1][3] = -vector_dot_product(cam_y, cam_eye);
    view.m[2][3] = -vector_dot_product(cam_z, cam_eye);
    view.m[3][3] = 1;

    printf("m[3][0]: %d\n", (int) (10000 * view.m[3][0]));
    printf("m[3][1]: %d\n", (int) (10000 * view.m[3][1]));
    printf("m[3][2]: %d\n", (int) (10000 * view.m[3][2]));

    print_point(v3);

    v1 = matmul_point_by_matrix_4(v1, view);
    v2 = matmul_point_by_matrix_4(v2, view);
    v3 = matmul_point_by_matrix_4(v3, view);

    print_point(v3);
    

    /*project the verticies of the triangle onto the screen*/
    point_t *triangle[3] = {&v1, &v2, &v3};
    for(int v = 0; v < 3; v++){
        /*double mag = 0.01 * vector_magnitude(*triangle[v]);
        printf("Mag: %d\n", (int) (10000 * mag));
        triangle[v]->x /= mag;
        triangle[v]->y /= mag;*/
        triangle[v]->x /= triangle[v]->z;
        triangle[v]->y /= triangle[v]->z;
    }

    v1 = convert_to_pixels(v1);
    v2 = convert_to_pixels(v2);
    v3 = convert_to_pixels(v3);

    print_point(v3);

    printf("About to iterate over pixels\n");

    /*draws triangle in 2d space first by making bounding box of points to check then using edge formula to see if point is inside triangle*/
    int width = gl_get_width();
    int height = gl_get_height();

    int box_x_min = min(v1.x, v2.x, v3.x);
    int box_x_max = max(v1.x, v2.x, v3.x);
    int box_y_min = min(v1.y, v2.y, v3.y);
    int box_y_max = max(v1.y, v2.y, v3.y);
    
    printf("Box x: %d --> %d\n", box_x_min, box_x_max);
    printf("Box y: %d --> %d\n", box_y_min, box_y_max);

    for(int box_x = box_x_min; box_x <= box_x_max; box_x++) {
        for(int box_y = box_y_min; box_y <= box_y_max; box_y++) {
            point_t in_tri = {.x = box_x, .y = box_y};
            if(edge(v1, v2, in_tri) && edge(v2, v3, in_tri) && edge(v3, v1, in_tri)) {
                gl_draw_pixel(box_x + width/2, -box_y + height/2, c);
            }
        }
    }
}

void gl_3d_clear(color_t c){
    gl_clear(c);
    clear_z_buf();
}


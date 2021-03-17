#include "gl_3d.h"
#include "malloc.h"
#include "printf.h"
#include "fb.h"

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
    //clear the z buff on initialization
    clear_z_buf();    
}

static double edge(point_t v1, point_t v2, point_t p){
    return ((p.x - v1.x) * (v2.y - v1.y) - (p.y - v1.y) * (v2.x - v1.x));
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

/*Takes in color c and double brightness between 0 and 1 and scales c by brightness then returns c*/
color_t compute_shade(color_t c, double brightness) {
    color_t ret = 0xff000000;
    ret |= (unsigned char)(((c >> 16) & 0xff) * brightness) << 16;
    ret |= (unsigned char)(((c >> 8) & 0xff) * brightness) << 8;
    ret |= (unsigned char)((c & 0xff) * brightness);
    return ret;
}

static double compute_depth(point_t v1, point_t v2, point_t v3, point_t p){
    double area_full_tri = edge(v1, v2, v3);
    return ((edge(v2, v3, p)*v1.z)/area_full_tri + (edge(v3, v1, p)*v2.z)/area_full_tri + (edge(v1, v2, p)*v3.z)/area_full_tri);
}

void gl_3d_draw_triangle_with_normal(point_t v1, point_t v2, point_t v3, point_t normal, matrix_4_t cam, matrix_4_t light, color_t c) {
    //distant light source scaling of color
    print_point(normal);
    point_t light_vec = {-light.m[0][2], -light.m[1][2], -light.m[2][2]};
    //print_point(light_vec);

    double cos_normal_light = vector_dot_product(normal, light_vec) / (vector_magnitude(normal) * vector_magnitude(light_vec));
    printf("Cos normal: %d\n", (int) (10000 * cos_normal_light));
    if (cos_normal_light < 0) cos_normal_light = 0;
    c = compute_shade(c, cos_normal_light);

    gl_3d_draw_triangle(v1, v2, v3, cam, light, c);
}

void gl_3d_draw_triangle(point_t v1, point_t v2, point_t v3, matrix_4_t cam, matrix_4_t light, color_t c) {

    /*if (cos_normal_light < 0) {
        normal_to_tri = (point_t) {-normal_to_tri.x, -normal_to_tri.y, -normal_to_tri.z};
        cos_normal_light = vector_dot_product(normal_to_tri, light_vec) / (vector_magnitude(normal_to_tri) * vector_magnitude(light_vec));
        printf("Cos normal: %d\n", (int) (10000 * cos_normal_light));
    }*/
    
    
    
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

    //printf("m[3][0]: %d\n", (int) (10000 * view.m[3][0]));
    //printf("m[3][1]: %d\n", (int) (10000 * view.m[3][1]));
    //printf("m[3][2]: %d\n", (int) (10000 * view.m[3][2]));

    //print_point(v1);

    v1 = matmul_point_by_matrix_4(v1, view);
    v2 = matmul_point_by_matrix_4(v2, view);
    v3 = matmul_point_by_matrix_4(v3, view);

    //print_point(v1);

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

    //print_point(v3);

    //printf("About to iterate over pixels\n");

    /*draws triangle in 2d space first by making bounding box of points to check then using edge formula to see if point is inside triangle*/
    int width = gl_get_width();
    int height = gl_get_height();

    int box_x_min = min(v1.x, v2.x, v3.x) < -(width/2) ? -(width/2) : min(v1.x, v2.x, v3.x);
    int box_x_max = max(v1.x, v2.x, v3.x) > width/2 ? width/2 : max(v1.x, v2.x, v3.x);
    int box_y_min = min(v1.y, v2.y, v3.y) < -(height/2) ? height/2 : min(v1.y, v2.y, v3.y);
    int box_y_max = max(v1.y, v2.y, v3.y) > height/2 ? height/2 : max(v1.y, v2.y, v3.y);
    
    //printf("Box x: %d --> %d\n", box_x_min, box_x_max);
    //printf("Box y: %d --> %d\n", box_y_min, box_y_max);
    
    //gl_draw_line(v1.x + width/2, -v1.y + height/2, v2.x + width/2, -v2.y + height/2, GL_RED);
    //gl_draw_line(v2.x + width/2, -v2.y + height/2, v3.x + width/2, -v3.y + height/2, GL_RED);
    //gl_draw_line(v3.x + width/2, -v3.y + height/2, v1.x + width/2, -v1.y + height/2, GL_RED);

    for(int box_x = box_x_min; box_x <= box_x_max; box_x++) {
        for(int box_y = box_y_min; box_y <= box_y_max; box_y++) {
            point_t in_tri = {.x = box_x, .y = box_y};
            if(edge(v1, v2, in_tri) >= 0 && edge(v2, v3, in_tri) >= 0 && edge(v3, v1, in_tri) >= 0) {
                point_t point = {box_x, box_y, 1};
                unsigned int pixel_x = box_x + width/2;
                unsigned int pixel_y = -box_y + height/2;
                double z = compute_depth(v1, v2, v3, point);
                //printf("%d\n", (int)(z*10000));
                unsigned int (*z_buf_2d)[width] = (void *)z_buf;
                //printf("%x\n", z_buf_2d[pixel_y][pixel_x]);
                if (z < z_buf_2d[pixel_y][pixel_x]) {
                    z_buf_2d[pixel_y][pixel_x] = z;
                    unsigned int per_row = fb_get_pitch()/4;
                    unsigned int (*im)[per_row] = fb_get_draw_buffer();
                    im[pixel_y][pixel_x] = c; 
                    //gl_draw_pixel(pixel_x, pixel_y, c);
                }
            }
        }
    }
}

void gl_3d_clear(color_t c){
    gl_clear(c);
    clear_z_buf();
}


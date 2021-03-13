#include "gl_3d.h"
#include "malloc.h"

#define INFINITY 0xffffffff
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

void gl_3d_draw_triangle(point_t v1, point_t v2, point_t v3, point_t cam, point_t light, color_t c) {
    double box_x_min = min(v1.x, v2.x, v3.x);
    double box_x_max = max(v1.x, v2.x, v3.x);

    double box_y_min = min(v1.y, v2.y, v3.y);
    double box_y_max = max(v1.y, v2.y, v3.y);

    for(int box_x = box_x_min; box_x <= box_x_max; box_x++){
        for(int box_y = box_y_min; box_y <= box_y_max; box_y++){
            point_t in_tri = {.x = box_x, .y = box_y};
            if(edge(v1, v2, in_tri) && edge(v2, v3, in_tri) && edge(v3, v1, in_tri)){ 
                gl_draw_pixel(box_x, box_y, c);
            }
        }
    }
}

void gl_3d_clear(color_t c){
    gl_clear(c);
    clear_z_buf();
}


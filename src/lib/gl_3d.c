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

void gl_3d_init() {
    z_buf = malloc(sizeof(unsigned int) * gl_get_width() * gl_get_height());    
}


void gl_3d_draw_triangle(point_t v1, point_t v2, point_t v3, point_t cam, point_t light){}


void gl_3d_clear(){
    gl_clear();
    clear_z_buf();
}


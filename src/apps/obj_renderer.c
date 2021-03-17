#include "uart.h"
#include "printf.h"
#include "obj_parser.h"
#include "gl.h"
#include "gl_3d.h"
#include "vector_math.h"
#include "math.h"
#include "malloc.h"
#include "timer.h"
#include "transform.h"

void main(void) {
    uart_init();
    gl_init(640, 512, GL_SINGLEBUFFER);
    gl_3d_init();
    obj_model_init();

    gl_3d_clear(GL_BLACK);

    obj_model_t *cube = obj_model_load("cube.obj");
    color_t colors[6] = {GL_AMBER, GL_MAGENTA, GL_BLUE, GL_MOSS, GL_CYAN, GL_RED};

    matrix_4_t cam;
    cam = transform_reset_rotation(cam);
    cam = transform_set_position(cam, 0, 3, -7);
    cam = transform_rotate_y(cam, PI/4);

    printf("About to draw triangles\n");
    for (int i = 0; i < cube->num_faces; i++) {
        gl_3d_draw_triangle(
                *(cube->faces[i].v1),
                *(cube->faces[i].v2),
                *(cube->faces[i].v3),
                cam, 
                cam,
                colors[i % 6]);
        printf("Drew triangle #%d\n", i);
        //timer_delay(1);
    }
    printf("Drew all triangles\n");
    
    uart_putchar(EOT);
}

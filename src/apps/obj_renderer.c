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

    obj_model_t *cube = obj_model_load("monkey.obj");
    //color_t colors[6] = {GL_AMBER, GL_MAGENTA, GL_BLUE, GL_MOSS, GL_CYAN, GL_RED};

    matrix_4_t cam;
    cam = transform_reset_rotation(cam);
    //cam = transform_set_position(cam, 0, 3, -5);
    //cam = transform_rotate_y(cam, PI/4);
    cam = transform_set_position(cam, 0, 3, 5);
    cam = transform_rotate_y(cam, PI);
    cam = transform_rotate_z(cam, PI);

    matrix_4_t light;
    light = transform_reset_rotation(light);
    //light = transform_set_position(light, 1, 4, 7);
    light = transform_rotate_x(light, PI/4);
    light = transform_rotate_y(light, PI);

    printf("About to draw triangles\n");
    for (int i = 0; i < cube->num_faces; i++) {
        gl_3d_draw_triangle_with_normal(
                *(cube->faces[i].v1),
                *(cube->faces[i].v2),
                *(cube->faces[i].v3),
                *(cube->faces[i].normal),
                cam, 
                light,
                //colors[i % 6]);
                GL_WHITE);
        printf("Drew triangle #%d\n", i);
        //timer_delay(5);
    }
    printf("Drew all triangles\n");
    
    uart_putchar(EOT);
}

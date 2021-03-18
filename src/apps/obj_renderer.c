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

void draw_triangles(obj_model_t *model, matrix_4_t cam, matrix_4_t light, color_t c);
void draw_cube(obj_model_t *model, color_t c);
void draw_monkey(obj_model_t *model, color_t c);
void rotate_cube(void);
void rotate_monkey(obj_model_t *model, color_t c);

void draw_monkey(obj_model_t *model, color_t c){
    matrix_4_t cam;
    cam = transform_reset_rotation(cam);
    cam = transform_set_position(cam, 0, 0, 10);
    cam = transform_rotate_z(cam, PI);
    cam = transform_rotate_y(cam, PI);

    matrix_4_t light;
    light = transform_reset_rotation(light);
    light = transform_rotate_x(light, PI/4);
    light = transform_rotate_y(light, PI);

    draw_triangles(model, cam, light, c);
}

void rotate_cube(void){
    
}

void rotate_monkey(obj_model_t *model, color_t c){
    for (int i = 0; i < 13; i++){
        double x = sin(i * (PI/6)) * sin(i * (PI/6)) * 10;
        double z = cos(i * (PI/6)) * cos(i * (PI/6)) * 10;
        matrix_4_t cam;
        cam = transform_reset_rotation(cam);
        cam = transform_set_position(cam, x, 0, z);
        cam = transform_rotate_z(cam, PI);
        cam = transform_rotate_y(cam, PI + (i * (PI/6)));

        matrix_4_t light;
        light = transform_reset_rotation(light);
        light = transform_rotate_x(light, PI/4);
        light = transform_rotate_y(light, PI + (i * (PI/6)));

        draw_triangles(model, cam, light, c);
        timer_delay(2);
        gl_3d_clear(GL_BLACK);
    }
}
void draw_triangles(obj_model_t *model, matrix_4_t cam, matrix_4_t light, color_t c){
    //printf("About to draw triangles\n");
    for (int i = 0; i < model->num_faces; i++) {
        gl_3d_draw_triangle_with_normal(
                *(model->faces[i].v1),
                *(model->faces[i].v2),
                *(model->faces[i].v3),
                *(model->faces[i].normal),
                cam, 
                light,
                //colors[i % 6]);
                c);
        //printf("Drew triangle #%d\n", i);
        //timer_delay(5);
    }
    //printf("Drew all triangles\n");
}

void main(void) {
    uart_init();
    gl_init(640, 480, GL_SINGLEBUFFER);
    gl_3d_init();
    obj_model_init();

    gl_3d_clear(GL_BLACK);
    color_t colors[7] = {GL_AMBER, GL_MAGENTA, GL_BLUE, GL_MOSS, GL_CYAN, GL_RED, GL_WHITE};

    obj_model_t *model = obj_model_load("monkey.obj");
    //draw_cube(GL_AMBER);
    //gl_3d_clear(GL_BLACK);
    //for (int i = 0; i < sizeof(colors)/4; i++){
	//gl_3d_clear(GL_BLACK);
        //draw_monkey (model, colors[i]);
	//timer_delay(2);
    //}
    //rotate_cube();
    rotate_monkey(model, GL_RED);
    
    uart_putchar(EOT);
}

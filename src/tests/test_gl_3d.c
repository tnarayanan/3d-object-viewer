#include "timer.h"
#include "printf.h"
#include "gl_3d.h"
#include "assert.h"
#include "uart.h"

void test_gl_3d_clear(void){
    gl_3d_clear(GL_BLUE);
    timer_delay(1);
    gl_3d_clear(GL_WHITE);
    timer_delay(1);
    gl_3d_clear(GL_BLACK);
    timer_delay(1);
}

void test_gl_3d_draw_triangle(void){
    gl_3d_clear(GL_BLACK);

    point_t v1 = {.x = 10, .y = 10};
    //gl_draw_pixel(v1.x, v1.y, GL_CYAN);

    point_t v2 = {.x = 10, .y = 200};
    //gl_draw_pixel(v2.x, v2.y, GL_CYAN);

    point_t v3 = {.x = 100, .y = 100};
    //gl_draw_pixel(v3.x, v3.y, GL_CYAN);
    
    color_t colors[5] = {GL_MAGENTA, GL_BLUE, GL_AMBER, GL_MOSS, GL_CYAN};
    for(int i = 0; i < (sizeof(colors)/4); i++){
        gl_3d_draw_triangle(v1, v2, v3, v1, v2, colors[i]);
        v1.x += 50;
        v2.x += 50;
        v3.x += 50;
        timer_delay_ms(500);
    }   
}

void main(void) {
    const int WIDTH = 640;
    const int HEIGHT = 512;

    gl_init(WIDTH, HEIGHT, GL_SINGLEBUFFER);
    gl_3d_init();

    printf("Running gl tests...\n");

    //test_gl_3d_clear();
    test_gl_3d_draw_triangle();

    printf("Finished running gl tests\n");
    uart_putchar(EOT);
} 


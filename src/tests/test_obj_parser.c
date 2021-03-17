#include "uart.h"
#include "printf.h"
#include "obj_parser.h"

void test_read_cube(void) {
    obj_model_t *cube = obj_model_load("cube.obj");

    printf("Cube has %d vertices and %d faces\n", cube->num_vertices, cube->num_faces);
    printf("Vertices:\n");
    for (int i = 0; i < cube->num_vertices; i++) {
        printf("    v%d: %d %d %d\n", i,
                (int) (cube->vertices[i].x * 1000000),
                (int) (cube->vertices[i].y * 1000000),
                (int) (cube->vertices[i].z * 1000000));
    }
    printf("Faces:\n");
    for (int i = 0; i < cube->num_faces; i++) {
        printf("    f%d v1 x: %d\n", i,
                (int) (cube->faces[i].v1->x * 1000000));
    }
    printf("End of cube info\n");
}

void main(void) {
    uart_init();
    printf("Running OBJ parser tests...\n");

    obj_model_init();
    test_read_cube();

    printf("Finished running OBJ parser tests\n");
    uart_putchar(EOT);
}

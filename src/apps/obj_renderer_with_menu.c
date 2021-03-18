#include "uart.h"
#include "printf.h"
#include "obj_parser.h"
#include "gl.h"
#include "gl_3d.h"
#include "vector_math.h"
#include "transform.h"
#include "keyboard.h"
#include "ps2_keys.h"
#include "ff.h"
#include "strings.h"
#include "assert.h"

#define MAX_OBJ_FILES 10

#define WIDTH 640
#define HEIGHT 480

#define CURSOR_COL_WIDTH 30

void circle_left() {}
void circle_right() {}

void render(char *filename) {
    obj_model_t *model = obj_model_load(filename);

    matrix_4_t cam;
    cam = transform_reset_rotation(cam);
    cam = transform_set_position(cam, 0, 0, 10);
    cam = transform_rotate_z(cam, PI);
    cam = transform_rotate_y(cam, PI);

    matrix_4_t light;
    light = transform_reset_rotation(light);
    light = transform_rotate_x(light, PI/4);
    light = transform_rotate_y(light, PI);

    while (true) {
        gl_3d_clear(GL_BLACK);
        for (int i = 0; i < model->num_faces; i++) {
            gl_3d_draw_triangle_with_normal(
                *(model->faces[i].v1),
                *(model->faces[i].v2),
                *(model->faces[i].v3),
                *(model->faces[i].normal),
                cam, 
                light,
                GL_WHITE);
        }

        char ch = keyboard_read_next();

        if (ch == PS2_KEY_ARROW_LEFT) {
            circle_left();
        } else if (ch == PS2_KEY_ARROW_RIGHT) {
            circle_right();
        } else if (ch == PS2_KEY_ARROW_UP) {
            cam.m[2][3]--; // zoom in
        } else if (ch == PS2_KEY_ARROW_DOWN) {
            cam.m[2][3]++; // zoom out
        } else if (ch == 'q') {
            break;
        }
    }
    gl_3d_clear(GL_BLACK);
}

void main(void) {
    gl_init(WIDTH, HEIGHT, GL_SINGLEBUFFER);
    gl_3d_init();
    obj_model_init();
    keyboard_init(KEYBOARD_CLOCK, KEYBOARD_DATA);

    gl_3d_clear(GL_BLACK);

    unsigned int line_height = gl_get_char_height() + 5;

    gl_draw_string(CURSOR_COL_WIDTH, 0, "3DOVE (3D Object ViewEr)", GL_AMBER);
    gl_draw_string(CURSOR_COL_WIDTH, line_height, "Choose a file:", GL_AMBER);

    unsigned int line_offset = 3; // 3 lines at the top

    FATFS fs;
    FRESULT res;
    f_mount(&fs, "", 0);

    DIR dir;
    res = f_opendir(&dir, "obj");
    assert(res == FR_OK);

    char filepaths[MAX_OBJ_FILES][80]; // max 50 files

    FILINFO info;
    int num_files = 0;
    for (int i = 0; i < MAX_OBJ_FILES; i++) {
        res = f_readdir(&dir, &info);
        if (res != FR_OK || info.fname[0] == 0) break;

        if (info.fname[0] == '.') {
            // ignore . and ..
            i--;
            continue;
        }

        memcpy(filepaths[i], info.fname, strlen(info.fname) + 1);
        printf("File: %s\n", filepaths[i]);

        gl_draw_string(CURSOR_COL_WIDTH, (i+line_offset) * line_height, filepaths[i], GL_AMBER);
        num_files++;
    }

    int selected = 0;

    while (true) {
        gl_draw_rect(0, 0, CURSOR_COL_WIDTH, HEIGHT, GL_BLACK); // clear all cursors
        gl_draw_char(0, (selected+line_offset) * line_height, '>', GL_AMBER); // draw cursor

        char ch = keyboard_read_next();

        if (ch == PS2_KEY_ARROW_UP) {
            selected--;
            if (selected < 0) selected += num_files;
        } else if (ch == PS2_KEY_ARROW_DOWN) {
            selected++;
            if (selected >= num_files) selected -= num_files;
        } else if (ch == ' ') {
            printf("Selected file #%d\n", selected);
            char path[80];
            path[0] = 0;
            strlcat(path, "obj/", sizeof(path));
            strlcat(path, filepaths[selected], sizeof(path));
            render(path);
            
            gl_draw_string(CURSOR_COL_WIDTH, 0, "3DOVE (3D Object ViewEr)", GL_AMBER);
            gl_draw_string(CURSOR_COL_WIDTH, line_height, "Choose a file:", GL_AMBER);
            for (int i = 0; i < num_files; i++) {
                gl_draw_string(CURSOR_COL_WIDTH, (i+line_offset) * line_height, filepaths[i], GL_AMBER);
            }
        }
    }


}
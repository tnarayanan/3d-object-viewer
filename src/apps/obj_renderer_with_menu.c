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
#include "timer.h"

#define MAX_OBJ_FILES 10

#define WIDTH 640
#define HEIGHT 480

#define CURSOR_COL_WIDTH 30

typedef struct {
    float rx;
    float rz;
    float y;
    float initial_ry;
    float initial_dist;
    matrix_4_t light;
} initial_view_params_t;

static initial_view_params_t initial_cube_params, initial_monkey_params;

void initialize_matrices(void) {

    matrix_4_t cube_light = transform_reset_rotation(cube_light);
    cube_light = transform_rotate_y(cube_light, PI/3);
    cube_light = transform_rotate_x(cube_light, PI/3);

    initial_cube_params = (initial_view_params_t) {
        PI/6,
        0,
        5,
        PI/4,
        14.12,
        cube_light
    };

    matrix_4_t monkey_light = transform_reset_rotation(monkey_light);
    monkey_light = transform_rotate_y(monkey_light, 5*PI/6);
    monkey_light = transform_rotate_x(monkey_light, PI/6);

    initial_monkey_params = (initial_view_params_t) {
        0,
        0,
        0,
        PI,
        10,
        monkey_light
    };
}

void render(char *filename) {
    gl_3d_clear(GL_BLACK);
    char buf[80];
    buf[0] = 0;
    strlcat(buf, "Loading ", sizeof(buf));
    strlcat(buf, filename, sizeof(buf));
    strlcat(buf, "...", sizeof(buf));
    gl_draw_string(CURSOR_COL_WIDTH, 0, buf, GL_AMBER);

    obj_model_t *model = obj_model_load(filename);
    gl_3d_clear(GL_BLACK);


    initial_view_params_t init_params;

    if (strcmp(filename, "obj/cube.obj") == 0) {
        init_params = initial_cube_params;
    } else if (strcmp(filename, "obj/monkey.obj") == 0) {
        init_params = initial_monkey_params;
    } else {
        init_params = initial_cube_params; // some default value
    }

    color_t c = GL_WHITE;
    matrix_4_t cam;
    matrix_4_t light = init_params.light;
    float dist = init_params.initial_dist;
    float angle = init_params.initial_ry + PI;

    while (true) {
        gl_3d_clear(GL_BLACK);
        cam = transform_set_position(cam, dist * sin(angle), init_params.y, dist * cos(angle));
        cam = transform_reset_rotation(cam);
        cam = transform_rotate_y(cam, angle + PI);
        cam = transform_rotate_x(cam, init_params.rx);
        cam = transform_rotate_z(cam, init_params.rz);

        for (int i = 0; i < model->num_faces; i++) {
            gl_3d_draw_triangle_with_normal(
                *(model->faces[i].v1),
                *(model->faces[i].v2),
                *(model->faces[i].v3),
                *(model->faces[i].normal),
                cam, 
                light,
                c);
            //printf("Drew triangle #%d\n", i);
        }
        printf("Rendered.\n");

        char ch = keyboard_read_next();

        if (ch == PS2_KEY_ARROW_LEFT) {
            angle -= PI/16;
        } else if (ch == PS2_KEY_ARROW_RIGHT) {
            angle += PI/16;
        } else if (ch == PS2_KEY_ARROW_UP) {
            dist--; // zoom in
        } else if (ch == PS2_KEY_ARROW_DOWN) {
            dist++; // zoom out
        } else if (ch == 'q') {
            break;
        } else if (ch == 'z'){
            draw_z_buf();
            while (keyboard_read_next() != 'c');
        }
        switch (ch) {
	    case 'r':
	        c = GL_RED;
		break;
	    case 'g':
	        c = GL_GREEN;
		break;
	    case 'b':
	        c = GL_BLUE;
		break;
	    case 'c':
	        c = GL_CYAN;
		break;
	    case 'm':
	        c = GL_MAGENTA;
		break;
	    case 'y':
	        c = GL_YELLOW;
		break;
	    case 'a':
	        c = GL_AMBER;
		break;
	    case 'o':
	        c = GL_ORANGE;
		break;
	    case 'p':
	        c = GL_PURPLE;
		break;
            case 'i':
	        c = GL_INDIGO;
		break;
            case 's':
	        c = GL_SILVER;
		break;
	    case 'w':
	        c = GL_WHITE;
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

    initialize_matrices();

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

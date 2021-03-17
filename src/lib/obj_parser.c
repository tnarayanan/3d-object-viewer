#include "obj_parser.h"
#include "malloc.h"
#include "ff.h"
#include "strings.h"
#include "printf.h"
#include <stdbool.h>

static FATFS fs;
static bool reached_eof;

void obj_model_init(void) {
    f_mount(&fs, "", 0);
}

static char *read_line(FIL *fil) {
    char *buf = malloc(1024);
    int i = 0;
    unsigned int bytes_read;
    do {
        f_read(fil, &buf[i], 1, &bytes_read);
    } while (buf[i++] != '\n' && bytes_read == 1);
    buf[i] = '\0';
    reached_eof = (bytes_read == 0);
    return buf;
}

obj_model_t *obj_model_load(const char *path) {
    printf("Loading model '%s'...\n", path);

    obj_model_t *obj = malloc(sizeof(obj_model_t));

    FIL fil;
    f_open(&fil, path, FA_READ);
    
    char *line;

    do {
        line = read_line(&fil);
        if (line[0] == 'v' && line[1] == ' ') {
            // vertex
            obj->num_vertices++;
        } else if (line[0] == 'f' && line[1] == ' ') {
            // face
            obj->num_faces++;
        }
        free(line);
    } while (!reached_eof);

    f_lseek(&fil, 0);

    obj->vertices = malloc(sizeof(point_t) * obj->num_vertices);
    int num_vertices_processed = 0;

    obj->faces = malloc(sizeof(obj_face_t) * obj->num_faces);
    int num_faces_processed = 0;

    do {
        line = read_line(&fil);
        if (line[0] == 'v' && line[1] == ' ') {
            // vertex
            point_t *pt = &(obj->vertices[num_vertices_processed++]);
            const char *next_non_num;
            const char *start_num = line+2;

            int mul = 1;
            if (*start_num == '-') {
                mul = -1;
                start_num++; // skip a negative sign
            }

            unsigned int whole_part = strtonum(start_num, &next_non_num);
            unsigned int dec_part = strtonum(next_non_num + 1, &next_non_num); // skip a decimal point
            pt->x = mul * (whole_part + (dec_part / 1000000.0));

            mul = 1;
            if (*(next_non_num + 1) == '-') {
                mul = -1;
                next_non_num++; // skip a negative sign
            }

            whole_part = strtonum(next_non_num + 1, &next_non_num); // skip a space
            dec_part = strtonum(next_non_num + 1, &next_non_num); // skip a decimal point
            pt->y = mul * (whole_part + (dec_part / 1000000.0));

            mul = 1;
            if (*(next_non_num + 1) == '-') {
                mul = -1;
                next_non_num++; // skip a negative sign
            }

            whole_part = strtonum(next_non_num + 1, &next_non_num); // skip a space
            dec_part = strtonum(next_non_num + 1, &next_non_num); // skip a decimal point
            pt->z = mul * (whole_part + (dec_part / 1000000.0));
        } else if (line[0] == 'f' && line[1] == ' ') {
            // face
            obj_face_t *face = &(obj->faces[num_faces_processed++]);

            const char *next_non_num;

            unsigned int v_index = strtonum(&line[2], &next_non_num);
            strtonum(next_non_num + 1, &next_non_num); // skip slash
            strtonum(next_non_num + 1, &next_non_num); // skip slash
            face->v1 = &(obj->vertices[v_index-1]);

            v_index = strtonum(next_non_num + 1, &next_non_num); // skip space
            strtonum(next_non_num + 1, &next_non_num); // skip slash
            strtonum(next_non_num + 1, &next_non_num); // skip slash
            face->v2 = &(obj->vertices[v_index-1]);

            v_index = strtonum(next_non_num + 1, &next_non_num); // skip space
            face->v3 = &(obj->vertices[v_index-1]);
        }
        free(line);
    } while (!reached_eof);

    printf("Finished loading model '%s'...\n", path);
    return obj;
}

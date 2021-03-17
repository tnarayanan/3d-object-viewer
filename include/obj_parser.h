#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "vector_math.h"

typedef struct {
	point_t *v1;
	point_t *v2;
	point_t *v3;
	point_t *normal;
} obj_face_t;

typedef struct {
	unsigned int num_vertices;
	point_t *vertices;
	unsigned int num_faces;
	obj_face_t *faces;
	unsigned int num_normals;
	point_t *normals;
} obj_model_t;

void obj_model_init(void);

obj_model_t *obj_model_load(const char *path);

#endif

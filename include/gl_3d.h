#ifndef GL_3D
#define GL_3D

#include "gl.h"

typedef struct {
    float x;
    float y;
    float z;
} point_t;

/*User should call gl_init first, initializing the fb. gl_3d_init initializes the z-buffer*/
void gl_3d_init();

/**/
void gl_3d_draw_triangle(point_t v1, point_t v2, point_t v3, point_t cam, point_t light);

/*Should call gl_clear but then also clear the z buffer*/
void gl_3d_clear();

#endif

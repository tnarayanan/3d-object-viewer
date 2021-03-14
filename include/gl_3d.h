#ifndef GL_3D
#define GL_3D

#include "gl.h"
#include "vector_math.h"
#include "math.h"

/*User should call gl_init first, initializing the fb. gl_3d_init initializes the z-buffer*/
void gl_3d_init();

/**/
void gl_3d_draw_triangle(point_t v1, point_t v2, point_t v3, point_t cam, point_t light, color_t c);

/*Should call gl_clear but then also clear the z buffer*/
void gl_3d_clear();

#endif

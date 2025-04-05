#include "matrix.h"

mat4_t mat4_identity(void)
{
	mat4_t eye = {
	    .m = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
	return eye;
}

mat4_t mat4_make_scale(float sx, float sy, float sz)
{
	mat4_t eye = mat4_identity();
	eye.m[0][0] = sx;
	eye.m[1][1] = sy;
	eye.m[2][2] = sz;
	return eye;
}

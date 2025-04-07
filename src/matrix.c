#include "matrix.h"
#include "vector.h"

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

mat4_t mat4_make_translation(float tx, float ty, float tz)
{
	mat4_t eye = mat4_identity();
	eye.m[0][3] = tx;
	eye.m[1][3] = ty;
	eye.m[2][3] = tz;
	return eye;
}

vec4_t mat4_mul_vec4(mat4_t *m, vec4_t *v)
{
	vec4_t ret;
	ret.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z +
		m->m[0][3] * v->w;
	ret.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z +
		m->m[1][3] * v->w;
	ret.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z +
		m->m[2][3] * v->w;
	ret.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z +
		m->m[3][3] * v->w;

	return ret;
}

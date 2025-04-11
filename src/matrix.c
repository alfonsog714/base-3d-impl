#include "matrix.h"
#include "math.h"
#include "vector.h"
#include <math.h>

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

mat4_t mat4_make_rotation_x(float angle)
{
	mat4_t eye = mat4_identity();
	float c = cos(angle);
	float s = sin(angle);
	eye.m[1][1] = c;
	eye.m[1][2] = -s;
	eye.m[2][1] = s;
	eye.m[2][2] = c;
	return eye;
}

mat4_t mat4_make_rotation_y(float angle)
{
	mat4_t eye = mat4_identity();
	float c = cos(angle);
	float s = sin(angle);
	eye.m[0][0] = c;
	eye.m[0][2] = s;
	eye.m[2][0] = -s;
	eye.m[2][2] = c;
	return eye;
}

mat4_t mat4_make_rotation_z(float angle)
{
	mat4_t eye = mat4_identity();
	float c = cos(angle);
	float s = sin(angle);
	eye.m[0][0] = c;
	eye.m[0][1] = -s;
	eye.m[1][0] = s;
	eye.m[1][1] = c;
	return eye;
}

mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar)
{
	mat4_t eye = {0};
	float nf = (1 / tan(fov / 2));
	float z1 = (zfar) / (zfar - znear);
	float z2 = (-zfar * znear) / (zfar - znear);
	eye.m[0][0] = (aspect) * (nf);
	eye.m[1][1] = nf;
	eye.m[2][2] = z1;
	eye.m[2][3] = z2;
	eye.m[3][2] = 1.0;
	return eye;
}

vec4_t mat4_mul_vec4_project(mat4_t *m, vec4_t *v)
{
	vec4_t ret = mat4_mul_vec4(m, v);

	// This is the perspective divide. We avoid division by zero.
	if (ret.w != 0) {
		ret.x /= ret.w;
		ret.y /= ret.w;
		ret.z /= ret.w;
	}
	return ret;
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

mat4_t mat4_mul_mat4(mat4_t *a, mat4_t *b)
{
	mat4_t ret;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = (a->m[i][0] * b->m[0][j]) +
				      (a->m[i][1] * b->m[1][j]) +
				      (a->m[i][2] * b->m[2][j]) +
				      (a->m[i][3] * b->m[3][j]);
		}
	}
	return ret;
}

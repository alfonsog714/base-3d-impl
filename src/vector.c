#include "vector.h"
#include <math.h>

vec2_t project(int fov, vec3_t point)
{
	vec2_t projected_point = {.x = (fov * point.x) / point.z,
				  .y = (fov * point.y) / point.z};

	return projected_point;
}

vec3_t vec3_rotate_x(vec3_t *v, float angle)
{
	vec3_t rotated = {.x = v->x,
			  .y = v->y * cos(angle) - v->z * sin(angle),
			  .z = v->y * sin(angle) + v->z * cos(angle)};
	return rotated;
}

vec3_t vec3_rotate_y(vec3_t *v, float angle)
{
	vec3_t rotated = {.x = v->x * cos(angle) - v->z * sin(angle),
			  .y = v->y,
			  .z = v->x * sin(angle) + v->z * cos(angle)};
	return rotated;
}

vec3_t vec3_rotate_z(vec3_t *v, float angle)
{
	vec3_t rotated = {.x = v->x * cos(angle) - v->y * sin(angle),
			  .y = v->x * sin(angle) + v->y * cos(angle),
			  .z = v->z};
	return rotated;
}

float vec2_magnitude(vec2_t *v) { return sqrtf((v->x * v->x) + (v->y * v->y)); }

float vec3_magnitude(vec3_t *v)
{
	return sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

vec2_t vec2_add(vec2_t *a, vec2_t *b)
{
	vec2_t ret;
	ret.x = a->x + b->x;
	ret.y = a->y + b->y;
	return ret;
}

vec3_t vec3_add(vec3_t *a, vec3_t *b)
{
	vec3_t ret;
	ret.x = a->x + b->x;
	ret.y = a->y + b->y;
	ret.z = a->z + b->z;
	return ret;
}

vec2_t vec2_sub(vec2_t *a, vec2_t *b)
{
	vec2_t ret;
	ret.x = a->x - b->x;
	ret.y = a->y - b->y;
	return ret;
}

vec3_t vec3_sub(vec3_t *a, vec3_t *b)
{
	vec3_t ret;
	ret.x = a->x - b->x;
	ret.y = a->y - b->y;
	ret.z = a->z - b->z;
	return ret;
}

vec2_t vec2_mul(vec2_t *v, float scalar)
{
	vec2_t ret = {.x = v->x * scalar, .y = v->y * scalar};
	return ret;
}

vec2_t vec2_div(vec2_t *v, float scalar)
{
	vec2_t ret = {.x = v->x * 1 / scalar, .y = v->y * 1 / scalar};
	return ret;
}

vec3_t vec3_mul(vec3_t *v, float scalar)
{
	vec3_t ret = {
	    .x = v->x * scalar, .y = v->y * scalar, .z = v->z * scalar};
	return ret;
}

vec3_t vec3_div(vec3_t *v, float scalar)
{
	vec3_t ret = {.x = v->x * 1 / scalar,
		      .y = v->y * 1 / scalar,
		      .z = v->z * 1 / scalar};
	return ret;
}

vec3_t vec3_cross_product(vec3_t *a, vec3_t *b)
{
	vec3_t ret = {.x = a->y * b->z - a->z * b->y,
		      .y = a->z * b->x - a->x * b->z,
		      .z = a->x * b->y - a->y * b->x};

	return ret;
}

float vec2_dot_product(vec2_t *a, vec2_t *b)
{
	return a->x * b->x + a->y * b->y;
}

float vec3_dot_product(vec3_t *a, vec3_t *b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vec2_normalize(vec2_t *v)
{
	float magnitude = vec2_magnitude(v);
	v->x = v->x * 1 / magnitude;
	v->y = v->y * 1 / magnitude;
}

void vec3_normalize(vec3_t *v)
{
	float magnitude = vec3_magnitude(v);
	v->x = v->x * 1 / magnitude;
	v->y = v->y * 1 / magnitude;
	v->z = v->z * 1 / magnitude;
}

vec4_t vec4_from_vec3(vec3_t *v)
{
	vec4_t v4 = {.x = v->x, .y = v->y, .z = v->z, .w = 1.0};
	return v4;
}

vec3_t vec3_from_vec4(vec4_t *v)
{
	vec3_t v3 = {.x = v->x, .y = v->y, .z = v->z};
	return v3;
}

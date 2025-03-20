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

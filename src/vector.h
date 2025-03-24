#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x, y;
} vec2_t;

typedef struct {
	float x, y, z;
} vec3_t;

vec2_t project(int fov, vec3_t point);
vec3_t vec3_rotate_x(vec3_t *v, float angle);
vec3_t vec3_rotate_y(vec3_t *v, float angle);
vec3_t vec3_rotate_z(vec3_t *v, float angle);
float vec2_magnitude(vec2_t *v);
float vec3_magnitude(vec3_t *v);
vec2_t vec2_add(vec2_t *a, vec2_t *b);
vec3_t vec3_add(vec3_t *a, vec3_t *b);
vec2_t vec2_sub(vec2_t *a, vec2_t *b);
vec3_t vec3_sub(vec3_t *a, vec3_t *b);

#endif // !VECTOR_H

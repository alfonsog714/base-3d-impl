#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x, y;
} vec2_t;

typedef struct {
	float x, y, z;
} vec3_t;

typedef struct {
	float x, y, z, w;
} vec4_t;

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
vec2_t vec2_mul(vec2_t *v, float scalar);
vec2_t vec2_div(vec2_t *v, float scalar);
vec3_t vec3_mul(vec3_t *v, float scalar);
vec3_t vec3_div(vec3_t *v, float scalar);
vec3_t vec3_cross_product(vec3_t *a, vec3_t *b);
float vec2_dot_product(vec2_t *a, vec2_t *b);
float vec3_dot_product(vec3_t *a, vec3_t *b);
void vec2_normalize(vec2_t *v);
void vec3_normalize(vec3_t *v);
vec3_t vec3_from_vec4(vec4_t *v);
vec4_t vec4_from_vec3(vec3_t *v);

#endif // !VECTOR_H

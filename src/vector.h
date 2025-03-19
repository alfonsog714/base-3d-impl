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

#endif // !VECTOR_H

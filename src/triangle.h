#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include <stdint.h>

typedef struct {
	int a, b, c;
} face_t;

typedef struct {
	vec2_t points[3];
} triangle_t;

void draw_triangle(triangle_t *triangle, uint32_t color);
#endif // !TRIANGLE_H

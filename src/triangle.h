#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include <stdint.h>

typedef struct {
	int a, b, c;
	uint32_t color;
} face_t;

typedef struct {
	vec2_t points[3];
	uint32_t color;
	float depth;
} triangle_t;

void draw_triangle(triangle_t *triangle, uint32_t color);
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2,
			  uint32_t color);
#endif // !TRIANGLE_H

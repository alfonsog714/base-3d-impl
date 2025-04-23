#include "triangle.h"
#include "display.h"
#include "swap.h"
#include "vector.h"
#include <stdint.h>

static void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2,
				      int y2, uint32_t color);
static void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2,
				   int y2, uint32_t color);

static void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2,
				      int y2, uint32_t color)
{
	// m = Δy / Δx
	// m' = Δx / Δy
	float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
	float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

	float x_start = x0;
	float x_end = x0;

	// loop scanlines
	for (int y = y0; y <= y2; y++) {
		draw_line(x_start, y, x_end, y, color);
		x_start += inv_slope_1;
		x_end += inv_slope_2;
	}
}

static void fill_flat_top_triangle(int x0, int y0, int x1, int y1, int x2,
				   int y2, uint32_t color)
{
	float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
	float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

	float x_start = x2;
	float x_end = x2;

	for (int y = y2; y >= y0; y--) {
		draw_line(x_start, y, x_end, y, color);
		x_start -= inv_slope_1;
		x_end -= inv_slope_2;
	}
}

void draw_triangle(triangle_t *triangle, uint32_t color)
{
	draw_line(triangle->points[0].x, triangle->points[0].y,
		  triangle->points[1].x, triangle->points[1].y, color);
	draw_line(triangle->points[1].x, triangle->points[1].y,
		  triangle->points[2].x, triangle->points[2].y, color);
	draw_line(triangle->points[2].x, triangle->points[2].y,
		  triangle->points[0].x, triangle->points[0].y, color);
}

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2,
			  uint32_t color)
{
	// Sort the vertices by their y-coord (y0 < y1 < y2)
	if (y0 > y1) {
		int_swap(&y0, &y1);
		int_swap(&x0, &x1);
	}

	if (y1 > y2) {
		int_swap(&y1, &y2);
		int_swap(&x1, &x2);
	}

	if (y0 > y1) {
		int_swap(&y0, &y1);
		int_swap(&x0, &x1);
	}

	if (y1 == y2) {
		fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
	} else if (y0 == y1) {
		fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
	} else {
		// calculate mid point of triangle
		int m_y = y1;
		int m_x =
		    ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

		fill_flat_bottom_triangle(x0, y0, x1, y1, m_x, m_y, color);
		fill_flat_top_triangle(x1, y1, m_x, m_y, x2, y2, color);
	}
}

void draw_textured_triangle(int x0, int y0, float u0, float v0, int x1, int y1,
			    float u1, float v1, int x2, int y2, float u2,
			    float v2, uint32_t color, uint32_t *texture)
{
	// sort vertices by their y-coord
	if (y0 > y1) {
		int_swap(&y0, &y1);
		int_swap(&x0, &x1);
		float_swap(&u0, &u1);
		float_swap(&v0, &v1);
	}

	if (y1 > y2) {
		int_swap(&y1, &y2);
		int_swap(&x1, &x2);
		float_swap(&u1, &u2);
		float_swap(&v1, &v2);
	}

	if (y0 > y1) {
		int_swap(&y0, &y1);
		int_swap(&x0, &x1);
	}
}

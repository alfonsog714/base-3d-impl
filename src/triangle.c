#include "triangle.h"
#include "display.h"
#include "vector.h"

static void int_swap(int *a, int *b);
static void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int mx,
				      int my);
static void fill_flat_top_triangle(int x1, int y1, int x2, int y2, int mx,
				   int my);

static void int_swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

static void fill_flat_bottom_triangle(int x0, int y0, int x1, int y1, int mx,
				      int my)
{
}

static void fill_flat_top_triangle(int x1, int y1, int x2, int y2, int mx,
				   int my)
{
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

	// calculate mid point of triangle
	int m_y = y1;
	int m_x = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

	fill_flat_bottom_triangle(x0, y0, x1, y1, m_x, m_y);
	fill_flat_top_triangle(x1, y1, x2, y2, m_x, m_y);
}

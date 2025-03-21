#include "triangle.h"
#include "display.h"

void draw_triangle(triangle_t *triangle, uint32_t color)
{
	draw_line(triangle->points[0].x, triangle->points[0].y,
		  triangle->points[1].x, triangle->points[1].y, color);
	draw_line(triangle->points[1].x, triangle->points[1].y,
		  triangle->points[2].x, triangle->points[2].y, color);
	draw_line(triangle->points[2].x, triangle->points[2].y,
		  triangle->points[0].x, triangle->points[0].y, color);
}

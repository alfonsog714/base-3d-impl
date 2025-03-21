#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "display.h"
#include "mesh.h"
#include "triangle.h"
#include "vector.h"

#define FOV_FACTOR 640

/* GLOBALS */
bool is_running = false;

vec3_t camera_pos = {.x = 0, .y = 0, .z = -5};
vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0};
triangle_t triangles_to_render[N_MESH_FACES];
int previous_frame_time = 0;

/* FUNCTIONS */

void setup(void)
{
	color_buffer =
	    (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
	CHECK(color_buffer, "Color buffer allocation failed.");

	color_buffer_texture = SDL_CreateTexture(
	    renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
	    window_width, window_height);
}

void process_input(void)
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			is_running = false;
		}
		break;
	}
}

void update(void)
{
	int time_to_wait =
	    FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
		SDL_Delay(time_to_wait);
	}

	previous_frame_time = SDL_GetTicks();
	cube_rotation.x += 0.005;
	cube_rotation.y += 0.005;
	cube_rotation.z += 0.005;

	for (int i = 0; i < N_MESH_FACES; i++) {
		face_t mesh_face = mesh_faces[i];
		vec3_t face_vertices[3];
		face_vertices[0] = mesh_vertices[mesh_face.a - 1];
		face_vertices[1] = mesh_vertices[mesh_face.b - 1];
		face_vertices[2] = mesh_vertices[mesh_face.c - 1];

		triangle_t projected_triangle;
		for (int j = 0; j < 3; j++) {
			vec3_t transformed_vertex = face_vertices[j];
			transformed_vertex =
			    vec3_rotate_x(&transformed_vertex, cube_rotation.x);
			transformed_vertex =
			    vec3_rotate_y(&transformed_vertex, cube_rotation.y);
			transformed_vertex =
			    vec3_rotate_z(&transformed_vertex, cube_rotation.z);

			transformed_vertex.z -= camera_pos.z;

			vec2_t projected_point =
			    project(FOV_FACTOR, transformed_vertex);

			projected_point.x += (window_width / 2);
			projected_point.y += (window_height / 2);

			projected_triangle.points[j] = projected_point;
		}

		triangles_to_render[i] = projected_triangle;
	}
}

void render(void)
{
	for (int i = 0; i < N_MESH_FACES; i++) {
		triangle_t triangle = triangles_to_render[i];

		// draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3,
		// 	  0xFF00FFFF);
		// draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3,
		// 	  0xFF00FFFF);
		// draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3,
		// 	  0xFF00FFFF);
		draw_line(triangle.points[0].x, triangle.points[0].y,
			  triangle.points[1].x, triangle.points[1].y);
		draw_line(triangle.points[1].x, triangle.points[1].y,
			  triangle.points[2].x, triangle.points[2].y);
		draw_line(triangle.points[2].x, triangle.points[2].y,
			  triangle.points[0].x, triangle.points[0].y);
	}

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

int main(void)
{
	is_running = init_window();

	setup();

	while (is_running) {
		process_input();
		update();
		render();
	};

	destroy();
	return 0;
}

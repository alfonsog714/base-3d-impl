#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "array.h"
#include "display.h"
#include "mesh.h"
#include "triangle.h"
#include "vector.h"

#define FOV_FACTOR 640

/* GLOBALS */
static bool is_running = false;

static vec3_t camera_pos = {0, 0, 0};
static triangle_t *triangles_to_render = NULL;
static int previous_frame_time = 0;

/* FUNCTIONS */

void setup(void)
{
	color_buffer =
	    (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
	CHECK(color_buffer, "Color buffer allocation failed.");

	color_buffer_texture = SDL_CreateTexture(
	    renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
	    window_width, window_height);

	// load_cube_mesh_data();
	load_obj_file_data("./assets/cube.obj");
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
	mesh.rotation.x += 0.01;
	mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.01;

	triangles_to_render = NULL;
	int num_faces = array_length(mesh.faces);

	for (int i = 0; i < num_faces; i++) {
		face_t mesh_face = mesh.faces[i];
		vec3_t face_vertices[3];

		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];

		vec3_t transformed_vertices[3];
		for (int j = 0; j < 3; j++) {
			vec3_t transformed_vertex = face_vertices[j];

			transformed_vertex =
			    vec3_rotate_x(&transformed_vertex, mesh.rotation.x);
			transformed_vertex =
			    vec3_rotate_y(&transformed_vertex, mesh.rotation.y);
			transformed_vertex =
			    vec3_rotate_z(&transformed_vertex, mesh.rotation.z);

			transformed_vertex.z += 5;

			transformed_vertices[j] = transformed_vertex;
		}

		// Culling algorithm
		vec3_t vec_a = transformed_vertices[0];
		vec3_t vec_b = transformed_vertices[1];
		vec3_t vec_c = transformed_vertices[2];

		vec3_t a = vec3_sub(&vec_b, &vec_a);
		vec3_normalize(&a);
		vec3_t b = vec3_sub(&vec_c, &vec_a);
		vec3_normalize(&b);

		vec3_t normal_vector = vec3_cross_product(&a, &b);
		vec3_normalize(&normal_vector);

		vec3_t camera_ray = vec3_sub(&camera_pos, &vec_a);

		float dot = vec3_dot_product(&normal_vector, &camera_ray);
		if (dot < 0) {
			continue;
		}

		triangle_t projected_triangle;
		for (int j = 0; j < 3; j++) {
			vec2_t projected_point =
			    project(FOV_FACTOR, transformed_vertices[j]);

			projected_point.x += (window_width / 2);
			projected_point.y += (window_height / 2);

			projected_triangle.points[j] = projected_point;
		}
		array_push(triangles_to_render, projected_triangle);
	}
}

void render(void)
{
	int tri_count = array_length(triangles_to_render);
	for (int i = 0; i < tri_count; i++) {
		triangle_t triangle = triangles_to_render[i];
		// draw_triangle(&triangle, 0xFFFFFFFF);
		draw_filled_triangle(triangle.points[0].x, triangle.points[0].y,
				     triangle.points[1].x, triangle.points[1].y,
				     triangle.points[2].x, triangle.points[2].y,
				     0xFF00FF00);
	}

	array_free(triangles_to_render);
	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

void free_resources()
{
	array_free(mesh.vertices);
	array_free(mesh.faces);
	free(color_buffer);
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
	free_resources();

	return 0;
}

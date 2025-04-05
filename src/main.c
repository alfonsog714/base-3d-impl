#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "array.h"
#include "display.h"
#include "matrix.h"
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
	render_method = RENDER_WIRE;
	cull_method = CULL_BACKFACE;

	color_buffer =
	    (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
	CHECK(color_buffer, "Color buffer allocation failed.");

	color_buffer_texture = SDL_CreateTexture(
	    renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
	    window_width, window_height);

	load_cube_mesh_data();
	// load_obj_file_data("./assets/f22.obj");
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
		// this if chain is ugly as fuck. find a better way.
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			is_running = false;
		}
		if (event.key.keysym.sym == SDLK_1) {
			render_method = RENDER_WIRE_VERTEX;
		}
		if (event.key.keysym.sym == SDLK_2) {
			render_method = RENDER_WIRE;
		}
		if (event.key.keysym.sym == SDLK_3) {
			render_method = RENDER_FILL_TRIANGLE;
		}
		if (event.key.keysym.sym == SDLK_4) {
			render_method = RENDER_FILL_TRIANGLE_WIRE;
		}
		if (event.key.keysym.sym == SDLK_c) {
			cull_method = CULL_BACKFACE;
		}
		if (event.key.keysym.sym == SDLK_d) {
			cull_method = CULL_NONE;
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
	mesh.scale.x += 0.002;
	mesh.scale.y += 0.001;

	mat4_t scale_matrix =
	    mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);

	triangles_to_render = NULL;
	int num_faces = array_length(mesh.faces);

	for (int i = 0; i < num_faces; i++) {
		face_t mesh_face = mesh.faces[i];
		vec3_t face_vertices[3];

		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];

		vec4_t transformed_vertices[3];
		for (int j = 0; j < 3; j++) {
			vec4_t transformed_vertex =
			    vec4_from_vec3(&face_vertices[j]);

			transformed_vertex =
			    mat4_mul_vec4(&scale_matrix, &transformed_vertex);

			transformed_vertex.z += 5;

			transformed_vertices[j] = transformed_vertex;
		}

		// Culling algorithm
		if (cull_method == CULL_BACKFACE) {
			vec3_t vec_a = vec3_from_vec4(&transformed_vertices[0]);
			vec3_t vec_b = vec3_from_vec4(&transformed_vertices[1]);
			vec3_t vec_c = vec3_from_vec4(&transformed_vertices[2]);

			vec3_t a = vec3_sub(&vec_b, &vec_a);
			vec3_normalize(&a);
			vec3_t b = vec3_sub(&vec_c, &vec_a);
			vec3_normalize(&b);

			vec3_t normal_vector = vec3_cross_product(&a, &b);
			vec3_normalize(&normal_vector);

			vec3_t camera_ray = vec3_sub(&camera_pos, &vec_a);

			float dot =
			    vec3_dot_product(&normal_vector, &camera_ray);
			if (dot < 0) {
				continue;
			}
		}

		vec2_t projected_points[3];
		for (int j = 0; j < 3; j++) {
			projected_points[j] =
			    project(FOV_FACTOR,
				    vec3_from_vec4(&transformed_vertices[j]));

			projected_points[j].x += (window_width / 2);
			projected_points[j].y += (window_height / 2);
		}

		float avg_depth =
		    (transformed_vertices[0].z + transformed_vertices[1].z +
		     transformed_vertices[2].z) /
		    3.f;

		triangle_t projected_triangle = {
		    .points =
			{
			    {projected_points[0].x, projected_points[0].y},
			    {projected_points[1].x, projected_points[1].y},
			    {projected_points[2].x, projected_points[2].y},
			},
		    .color = mesh_face.color,
		    .depth = avg_depth};
		array_push(triangles_to_render, projected_triangle);
	}

	array_qsort(triangles_to_render);
}

void render(void)
{
	SDL_RenderClear(renderer);
	// draw_grid();
	int tri_count = array_length(triangles_to_render);
	for (int i = 0; i < tri_count; i++) {
		triangle_t triangle = triangles_to_render[i];
		if (render_method == RENDER_FILL_TRIANGLE ||
		    render_method == RENDER_FILL_TRIANGLE_WIRE) {
			draw_filled_triangle(
			    triangle.points[0].x, triangle.points[0].y,
			    triangle.points[1].x, triangle.points[1].y,
			    triangle.points[2].x, triangle.points[2].y,
			    triangle.color);
		}

		if (render_method == RENDER_FILL_TRIANGLE_WIRE ||
		    render_method == RENDER_WIRE ||
		    render_method == RENDER_WIRE_VERTEX) {
			draw_triangle(&triangle, 0xFFFFFFFF);
		}

		if (render_method == RENDER_WIRE_VERTEX) {
			draw_rect(triangle.points[0].x - 3,
				  triangle.points[0].y - 3, 6, 6, 0xFF0000FF);
			draw_rect(triangle.points[1].x - 3,
				  triangle.points[1].y - 3, 6, 6, 0xFF0000FF);
			draw_rect(triangle.points[2].x - 3,
				  triangle.points[2].y - 3, 6, 6, 0xFF0000FF);
		}
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

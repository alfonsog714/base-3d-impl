#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "display.h"
#include "vector.h"

#define N_POINTS 9 * 9 * 9
#define FOV_FACTOR 640

/* GLOBALS */
bool is_running = false;

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];
vec3_t camera_pos = {.x = 0, .y = 0, .z = -5};
vec3_t cube_rotation = {.x = 0, .y = 0, .z = 0};
int previous_frame_time = 0;

/* FUNCTIONS */

void setup(void)
{
	gColor_buffer = (uint32_t *)malloc(sizeof(uint32_t) * gWindow_width *
					   gWindow_height);
	CHECK(gColor_buffer, "Color buffer allocation failed.");

	gColor_buffer_texture = SDL_CreateTexture(
	    gRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING,
	    gWindow_width, gWindow_height);

	int point_counter = 0;
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t new_point = {.x = x, .y = y, .z = z};
				cube_points[point_counter] = new_point;
				point_counter++;
			}
		}
	}
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
	while (!SDL_TICKS_PASSED(SDL_GetTicks(),
				 previous_frame_time + FRAME_TARGET_TIME)) {
		;
	}

	previous_frame_time = SDL_GetTicks();
	cube_rotation.x += 0.005;
	cube_rotation.y += 0.005;
	cube_rotation.z += 0.005;

	for (int i = 0; i < N_POINTS; i++) {
		vec3_t point = cube_points[i];
		vec3_t transformed_point =
		    vec3_rotate_x(&point, cube_rotation.y);
		transformed_point =
		    vec3_rotate_y(&transformed_point, cube_rotation.x);
		transformed_point =
		    vec3_rotate_z(&transformed_point, cube_rotation.x);
		transformed_point.z -= camera_pos.z;

		vec2_t projected_point = project(FOV_FACTOR, transformed_point);
		projected_points[i] = projected_point;
	}
}

void render(void)
{
	// draw_grid();

	for (int i = 0; i < N_POINTS; i++) {
		vec2_t projected_point = projected_points[i];
		draw_rect((int)projected_point.x + gWindow_width / 2,
			  (int)projected_point.y + gWindow_height / 2, 4, 4,
			  0xFF00FFFF);
	}

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(gRenderer);
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

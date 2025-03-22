#include "display.h"
#include <math.h>
#include <stdlib.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

bool init_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		CHECK_SDL(0);
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_width = display_mode.w;
	window_height = display_mode.h;

	window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED, window_width,
				  window_height, SDL_WINDOW_BORDERLESS);
	CHECK_SDL(window);

	renderer = SDL_CreateRenderer(window, -1, 0);
	CHECK_SDL(renderer);

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;
}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < window_height; ++y) {
		for (int x = 0; x < window_width; ++x) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

void draw_pixel(int pos_x, int pos_y, uint32_t color)
{
	if (pos_x >= 0 && pos_y >= 0 && pos_x < window_width &&
	    pos_y < window_height) {
		color_buffer[(window_width * pos_y) + pos_x] = color;
	}
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t color)
{
	int delta_x = x1 - x0;
	int delta_y = y1 - y0;

	int side_length =
	    abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)side_length;
	float y_inc = delta_y / (float)side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i <= side_length; i++) {
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_grid(void)
{
	for (int y = 0; y < window_height; ++y) {
		for (int x = 0; x < window_width; ++x) {
			if (x % 10 == 0 || y % 10 == 0) {
				color_buffer[(window_width * y) + x] =
				    0xFF333333;
			}
		}
	}
}

void draw_rect(int pos_x, int pos_y, int w, int h, uint32_t color)
{
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int curr_x = x + pos_x;
			int curr_y = y + pos_y;
			draw_pixel(curr_x, curr_y, color);
		}
	}
}

void render_color_buffer()
{
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
			  (int)(window_width * sizeof(uint32_t)));

	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void destroy(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

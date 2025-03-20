#include "display.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
uint32_t *gColor_buffer = NULL;
SDL_Texture *gColor_buffer_texture = NULL;
int gWindow_width = 800;
int gWindow_height = 600;

bool init_window(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		CHECK_SDL(0);
	}

	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	gWindow_width = display_mode.w;
	gWindow_height = display_mode.h;

	gWindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
				   SDL_WINDOWPOS_CENTERED, gWindow_width,
				   gWindow_height, SDL_WINDOW_BORDERLESS);
	CHECK_SDL(gWindow);

	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
	CHECK_SDL(gRenderer);

	SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);

	return true;
}

void clear_color_buffer(uint32_t color)
{
	for (int y = 0; y < gWindow_height; ++y) {
		for (int x = 0; x < gWindow_width; ++x) {
			gColor_buffer[(gWindow_width * y) + x] = color;
		}
	}
}

void draw_pixel(int pos_x, int pos_y, uint32_t color)
{
	if (pos_x >= 0 && pos_y >= 0 && pos_x < gWindow_width &&
	    pos_y < gWindow_height) {
		gColor_buffer[(gWindow_width * pos_y) + pos_x] = color;
	}
}

void draw_grid(void)
{
	for (int y = 0; y < gWindow_height; ++y) {
		for (int x = 0; x < gWindow_width; ++x) {
			if (x % 10 == 0 || y % 10 == 0) {
				gColor_buffer[(gWindow_width * y) + x] =
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
	SDL_UpdateTexture(gColor_buffer_texture, NULL, gColor_buffer,
			  (int)(gWindow_width * sizeof(uint32_t)));

	SDL_RenderCopy(gRenderer, gColor_buffer_texture, NULL, NULL);
}

void destroy(void)
{
	free(gColor_buffer);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

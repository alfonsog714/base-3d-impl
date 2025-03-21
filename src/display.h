#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

/////////////////////////////////
// Macros
/////////////////////////////////

#define CHECK_SDL(object)                                                      \
	do {                                                                   \
		if (!(object)) {                                               \
			fprintf(stderr, "SDL Error: %s - %s:%d\n",             \
				SDL_GetError(), __FILE__, __LINE__);           \
			return 0;                                              \
		}                                                              \
	} while (0)

#define CHECK(object, message)                                                 \
	do {                                                                   \
		if (!(object)) {                                               \
			fprintf(stderr, "Error: %s - %s:%d\n", (message),      \
				__FILE__, __LINE__);                           \
		}                                                              \
	} while (0)

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

/////////////////////////////////
// Globals
/////////////////////////////////

extern int window_width, window_height;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

/////////////////////////////////
// Functions
/////////////////////////////////

bool init_window(void);
void clear_color_buffer(uint32_t color);
void draw_pixel(int pos_x, int pos_y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_grid(void);
void draw_rect(int pos_x, int pos_y, int w, int h, uint32_t color);
void render_color_buffer(void);
void destroy(void);

#endif // !DISPLAY_H

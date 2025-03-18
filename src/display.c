#include "display.h"

bool init_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    CHECK_SDL(0);
  }

  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  window_width = display_mode.w;
  window_height = display_mode.h;

  window =
      SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       window_width, window_height, SDL_WINDOW_BORDERLESS);
  CHECK_SDL(window);

  renderer = SDL_CreateRenderer(window, -1, 0);
  CHECK_SDL(renderer);

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  return true;
}

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; ++y) {
    for (int x = 0; x < window_width; ++x) {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

void draw_grid(void) {
  for (int y = 0; y < window_height; ++y) {
    for (int x = 0; x < window_width; ++x) {
      if (x % 10 == 0 || y % 10 == 0)
        color_buffer[(window_width * y) + x] = 0xFF333333;
    }
  }
}

void draw_rect(int pos_x, int pos_y, int w, int h, uint32_t color) {
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      int curr_x = x + pos_x;
      int curr_y = y + pos_y;
      color_buffer[(window_width * curr_y) + curr_x] = color;
    }
  }
}

void render_color_buffer() {
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)(window_width * sizeof(uint32_t)));

  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void destroy(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* MACROS */
#define CHECK_SDL(object)                                                      \
  do {                                                                         \
    if (!(object)) {                                                           \
      fprintf(stderr, "SDL Error: %s - %s:%d\n", SDL_GetError(), __FILE__,     \
              __LINE__);                                                       \
      return 0;                                                                \
    }                                                                          \
  } while (0)

#define CHECK(object, message)                                                 \
  do {                                                                         \
    if (!(object)) {                                                           \
      fprintf(stderr, "Error: %s - %s:%d\n", (message), __FILE__, __LINE__);   \
    }                                                                          \
  } while (0)

/* GLOBALS */
bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

/* FUNCTIONS */

bool initialize_window(void) {
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

void setup(void) {
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
  CHECK(color_buffer, "Color buffer allocation failed.");

  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           window_width, window_height);
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      is_running = false;
    break;
  }
}

void update(void) {}

void clear_color_buffer(uint32_t color) {
  for (int y = 0; y < window_height; ++y) {
    for (int x = 0; x < window_width; ++x) {
      color_buffer[(window_width * y) + x] = color;
    }
  }
}

void draw_grid() {
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

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  draw_grid();
  draw_rect(0, 0, 960, 540, 0xFFFF0000);
  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

void destroy(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  };

  destroy();
  return 0;
}

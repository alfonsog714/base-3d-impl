#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "display.h"

/* GLOBALS */
bool is_running = false;

/* FUNCTIONS */

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

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  draw_grid();
  draw_rect(0, 0, window_width / 2, window_height / 2, 0xFFFF0000);
  draw_pixel(window_width / 2, window_height / 2, 0xFF00FF00);
  render_color_buffer();
  clear_color_buffer(0xFF000000);

  SDL_RenderPresent(renderer);
}

int main(void) {
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

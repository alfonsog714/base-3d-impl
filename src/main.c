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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/* GLOBALS */
bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;

/* FUNCTIONS */

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    CHECK_SDL(0);
  }

  window =
      SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
  CHECK_SDL(window);

  renderer = SDL_CreateRenderer(window, -1, 0);
  CHECK_SDL(renderer);

  return true;
}

void setup(void) {
  color_buffer =
      (uint32_t *)malloc(sizeof(uint32_t) * SCREEN_WIDTH * SCREEN_HEIGHT);
  CHECK(color_buffer, "Color buffer allocation failed.");
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
  SDL_SetRenderDrawColor(renderer, 150, 150, 0, 255);
  SDL_RenderClear(renderer);

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

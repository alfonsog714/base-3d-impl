#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#define CHECK_SDL(object)                                                      \
  do {                                                                         \
    if (!(object)) {                                                           \
      fprintf(stderr, "SDL Error: %s - %s:%d\n", SDL_GetError(), __FILE__,     \
              __LINE__);                                                       \
      return 0;                                                                \
    }                                                                          \
  } while (0)

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    CHECK_SDL(0);
  }

  window =
      SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, SDL_WINDOW_BORDERLESS);
  CHECK_SDL(window);

  renderer = SDL_CreateRenderer(window, -1, 0);
  CHECK_SDL(renderer);

  return true;
}

void setup() {}

void process_input() {
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

void update() {}

void render() {
  SDL_SetRenderDrawColor(renderer, 150, 150, 0, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  };
  return 0;
}

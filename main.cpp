#include "SDL.h"
#include "SDL_video.h"
#include <cstdlib>
#include <iostream>
#include <stdint.h>

typedef struct {
  SDL_Window *window;
} sdl_t;

typedef struct {
  uint32_t window_width;
  uint32_t window_height;
} config_t;

bool init_sdl(sdl_t *sdl, config_t *config) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return false;
  }
  std::cout << "SDL initialized successfully!" << std::endl;
  sdl->window = SDL_CreateWindow("Chip8 emulator", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, config->window_width,
                                 config->window_height, 0);
  if (!sdl->window) {
    std::cerr << "Could not configure SDL window\n" << SDL_GetError();
    return false;
  }

  return true;
}

void final_cleanup(sdl_t *sdl) {
  SDL_DestroyWindow(sdl->window);
  SDL_Quit();
}

int main() {
  sdl_t sdl = {0};
  config_t config = {0};
  if (!init_sdl(&sdl, &config))
    exit(EXIT_FAILURE);
  final_cleanup(&sdl);

  exit(EXIT_SUCCESS);
  return 0;
}

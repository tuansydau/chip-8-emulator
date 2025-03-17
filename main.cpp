#include "SDL.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <cstdlib>
#include <iostream>
#include <stdbool.h>
#include <stdint.h>

// sdl window object
typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} sdl_t;

// sdl config object
typedef struct {
  uint32_t window_width;
  uint32_t window_height;
  uint32_t fg_colour;
  uint32_t bg_colour;
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
    std::cerr << "Could not configure SDL window\n"
              << SDL_GetError() << std::endl;
    return false;
  }

  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);

  if (!sdl->renderer) {
    std::cerr << "Could not configure SDL renderer\n"
              << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void final_cleanup(const sdl_t sdl) {
  SDL_DestroyWindow(sdl.window);
  SDL_DestroyRenderer(sdl.renderer);
  SDL_Quit();
}

void update_screen(const sdl_t sdl) { SDL_RenderPresent(sdl.renderer); }

bool set_config_from_args(config_t *config, const int argc, char **argv) {
  // Set defaults, then override the defaults
  *config = (config_t){
      .window_width = 64,
      .window_height = 32,
      .fg_colour = 0xFFFFFFFF,
      .bg_colour = 0x000000FF,
  };
  return true;
}

void clear_screen(const sdl_t sdl, const config_t config) {
  const uint8_t r = (config.bg_colour >> 24) & 0xFF;
  const uint8_t g = (config.bg_colour >> 16) & 0xFF;
  const uint8_t b = (config.bg_colour >> 8) & 0xFF;
  const uint8_t a = (config.bg_colour >> 0) & 0xFF;

  SDL_SetRenderDrawColor(sdl.renderer, r, g, b, a);
  SDL_RenderClear(sdl.renderer);
}

int main(int argc, char *argv[]) {
  config_t config = {0};

  set_config_from_args(&config, argc, argv);
  
  sdl_t sdl = {0};
  if (!init_sdl(&sdl, &config))
    exit(EXIT_FAILURE);

  clear_screen(sdl, config);

  // Game loop
//  while (true) {
//    SDL_Delay(16);
//    update_screen(sdl);
//  }

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }
    SDL_Delay(16);
    update_screen(sdl);
  }

  final_cleanup(sdl);
  exit(EXIT_SUCCESS);
  return 0;
}

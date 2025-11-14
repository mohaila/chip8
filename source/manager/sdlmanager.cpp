#include "sdlmanager.hpp"

SDLManager::SDLManager() {
  SDL_Init(SDL_INIT_VIDEO);
  auto width = 10 * CHIP8_VIDEO_WIDTH;
  auto height = 10 * CHIP8_VIDEO_HEIGHT;
  window = SDL_CreateWindow("CHIP-8 Emulator", 0, 0, width, height,
                            SDL_WINDOW_SHOWN);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_STREAMING, CHIP8_VIDEO_WIDTH,
                              CHIP8_VIDEO_HEIGHT);
}

SDLManager::~SDLManager() {
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void SDLManager::display(const int32_t* video) {
  SDL_UpdateTexture(texture, nullptr, video, pitch);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_RenderPresent(renderer);
}

bool SDLManager::handleKeys(bool* keys) {
  auto run = true;
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        run = false;
        break;
      case SDL_KEYDOWN:
        run = handleKeysDown(event, keys);
        break;
      case SDL_KEYUP:
        handleKeysUp(event, keys);
        break;
    }
  }
  return run;
}

void SDLManager::handleKeysUp(SDL_Event& event, bool* keys) {
  switch (event.key.keysym.sym) {
    case SDLK_x:
      keys[0] = false;
      break;
    case SDLK_1:
      keys[1] = false;
      break;
    case SDLK_2:
      keys[2] = false;
      break;
    case SDLK_3:
      keys[3] = false;
      break;
    case SDLK_q:
      keys[4] = false;
      break;
    case SDLK_w:
      keys[5] = false;
      break;
    case SDLK_e:
      keys[6] = false;
      break;
    case SDLK_a:
      keys[7] = false;
      break;
    case SDLK_s:
      keys[8] = false;
      break;
    case SDLK_d:
      keys[9] = false;
      break;
    case SDLK_z:
      keys[0xA] = false;
      break;
    case SDLK_c:
      keys[0xB] = false;
      break;
    case SDLK_4:
      keys[0xC] = false;
      break;
    case SDLK_r:
      keys[0xD] = false;
      break;
    case SDLK_f:
      keys[0xE] = false;
      break;
    case SDLK_v:
      keys[0xF] = false;
      break;
  }
}

bool SDLManager::handleKeysDown(SDL_Event& event, bool* keys) {
  bool run = true;
  switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      run = false;
      break;
    case SDLK_x:
      keys[0] = true;
      break;
    case SDLK_1:
      keys[1] = true;
      break;
    case SDLK_2:
      keys[2] = true;
      break;
    case SDLK_3:
      keys[3] = true;
      break;
    case SDLK_q:
      keys[4] = true;
      break;
    case SDLK_w:
      keys[5] = true;
      break;
    case SDLK_e:
      keys[6] = true;
      break;
    case SDLK_a:
      keys[7] = true;
      break;
    case SDLK_s:
      keys[8] = true;
      break;
    case SDLK_d:
      keys[9] = true;
      break;
    case SDLK_z:
      keys[0xA] = true;
      break;
    case SDLK_c:
      keys[0xB] = true;
      break;
    case SDLK_4:
      keys[0xC] = true;
      break;
    case SDLK_r:
      keys[0xD] = true;
      break;
    case SDLK_f:
      keys[0xE] = true;
      break;
    case SDLK_v:
      keys[0xF] = true;
      break;
  }
  return run;
}
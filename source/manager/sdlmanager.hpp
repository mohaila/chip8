#pragma once

#include "chip8/emulator.hpp"
#include "pch.h"

class SDLManager : public Chip8HardwareManager {
 private:
  SDLManager(const SDLManager&) = delete;
  SDLManager& operator=(const SDLManager&) = delete;

 public:
  SDLManager();
  virtual ~SDLManager();

  virtual void display(const int32_t* video) override;
  virtual bool handleKeys(bool* keys) override;

 private:
  void handleKeysUp(SDL_Event& event, bool* keys);
  bool handleKeysDown(SDL_Event& event, bool* keys);

 private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Texture* texture = nullptr;
  int32_t pitch = CHIP8_VIDEO_WIDTH * sizeof(int32_t);
};
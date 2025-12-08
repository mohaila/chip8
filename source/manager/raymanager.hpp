#pragma once

#include "chip8/emulator.hpp"
#include "pch.h"

class RayManager : public Chip8HardwareManager {
 private:
  RayManager(const RayManager&) = delete;
  RayManager& operator=(const RayManager&) = delete;

 public:
  RayManager();
  virtual ~RayManager();

  virtual void display(const int32_t* video) override;
  virtual bool handleKeys(bool* keys) override;

 private:
  void handleKeysUp(bool* keys);
  void handleKeysDown(bool* keys);

 private:
  int32_t pitch = CHIP8_VIDEO_WIDTH * sizeof(int32_t);
};
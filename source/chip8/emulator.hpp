#pragma once

#include "chip8.hpp"

#define CHIP8_DELAY 10

using std::string;

class Chip8HardwareManager {
 private:
  Chip8HardwareManager(const Chip8HardwareManager&) = delete;
  Chip8HardwareManager& operator=(const Chip8HardwareManager&) = delete;

 public:
  Chip8HardwareManager() = default;
  virtual ~Chip8HardwareManager() = default;

  virtual void display(const int32_t* video) = 0;
  virtual bool handleKeys(bool* keys) = 0;
};

class Chip8Emulator {
 private:
  Chip8Emulator(const Chip8Emulator&) = delete;
  Chip8Emulator& operator=(const Chip8Emulator&) = delete;

 public:
  Chip8Emulator(Chip8HardwareManager* hm);
  ~Chip8Emulator();

  void execute(const string& romfile);

 private:
  Chip8HardwareManager* hardwareManager = nullptr;
  Chip8 chip8{};
  bool validROM = false;
};
#pragma once

#include "chip8.hpp"

using std::string;

class ROMLoader {
 private:
  ROMLoader(const ROMLoader&) = delete;
  ROMLoader operator=(const ROMLoader&) = delete;

 public:
  ROMLoader() = default;
  ~ROMLoader() = default;

  bool loadROM(Chip8& chip8, const string& filename);
};

class FontLoader {
 private:
  FontLoader(const FontLoader&) = delete;
  FontLoader operator=(const FontLoader&) = delete;

 public:
  FontLoader() = default;
  ~FontLoader() = default;

  void loadFont(Chip8& chip8);
  uint8_t getFont(uint8_t digit, uint8_t index) const;

 private:
  static uint8_t font[CHIP8_FONTS * CHIP8_FONT_SIZE];
};
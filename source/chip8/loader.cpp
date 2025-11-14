#include "loader.hpp"

using std::cerr;
using std::endl;
using std::ifstream;
using std::ios;

bool ROMLoader::loadROM(Chip8& chip8, const string& filename) {
  ifstream rom{filename, ios::binary};
  if (!rom.is_open()) {
    cerr << "failed to open ROM: " << filename << endl;
    return false;
  }
  rom.seekg(0, ios::end);
  auto romSize = rom.tellg();
  if (romSize == 0) {
    cerr << "invalid ROM size: " << romSize << endl;
    return false;
  }

  if (romSize > CHIP8_MEMORY_SIZE - CHIP8_MEMORY_START) {
    cerr << "invalid ROM size: " << romSize << endl;
    return false;
  }

  auto buffer = new char[romSize];

  rom.seekg(0, ios::beg);
  rom.read(buffer, romSize);
  rom.close();

  memcpy(chip8.memory + CHIP8_MEMORY_START, buffer, romSize);

  delete[] buffer;

  return true;
}

uint8_t FontLoader::font[CHIP8_FONTS * CHIP8_FONT_SIZE] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,  // 0
    0x20, 0x60, 0x20, 0x20, 0x70,  // 1
    0xf0, 0x10, 0xf0, 0x80, 0xf0,  // 2
    0xf0, 0x10, 0xf0, 0x10, 0xf0,  // 3
    0x90, 0x90, 0xf0, 0x10, 0x10,  // 4
    0xf0, 0x80, 0xf0, 0x10, 0xf0,  // 5
    0xf0, 0x80, 0xf0, 0x90, 0xf0,  // 6
    0xf0, 0x10, 0x20, 0x40, 0x40,  // 7
    0xf0, 0x90, 0xf0, 0x90, 0xf0,  // 8
    0xf0, 0x90, 0xf0, 0x10, 0xf0,  // 9
    0xf0, 0x90, 0xf0, 0x90, 0x90,  // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
    0xf0, 0x80, 0x80, 0x80, 0xf0,  // C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
    0xf0, 0x80, 0xf0, 0x80, 0xf0,  // E
    0xf0, 0x80, 0xf0, 0x80, 0x80   // F
};

void FontLoader::loadFont(Chip8& chip8) {
  memcpy(chip8.memory + CHIP8_FONTS_START, font, sizeof(font));
}

uint8_t FontLoader::getFont(uint8_t digit, uint8_t index) const {
  auto start = digit * CHIP8_FONT_SIZE;
  return font[start + index];
}

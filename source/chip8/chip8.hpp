#pragma once

#include "pch.h"

#define CHIP8_MEMORY_SIZE 4096
#define CHIP8_MEMORY_START 0x200
#define CHIP8_REGS 16
#define CHIP8_KEYS 16
#define CHIP8_FONTS 16
#define CHIP8_FONT_SIZE 0x05
#define CHIP8_FONTS_START 0x50
#define CHIP8_STACK 16
#define CHIP8_VIDEO_HEIGHT 32
#define CHIP8_VIDEO_WIDTH 64

using std::vector;

class Chip8 {
 private:
  Chip8(const Chip8&) = delete;
  Chip8& operator=(const Chip8&) = delete;

 public:
  Chip8();
  ~Chip8() = default;

  void reset();
  void execute();
  void setMemory(uint16_t start, const vector<uint8_t>& code);
  void setVideo(uint16_t start, const vector<int32_t>& screen);
  void setStack(const vector<uint16_t>& addrs);

  uint8_t memory[CHIP8_MEMORY_SIZE];
  int32_t video[CHIP8_VIDEO_WIDTH * CHIP8_VIDEO_HEIGHT];
  uint8_t registers[CHIP8_REGS];
  uint16_t stack[CHIP8_STACK];
  bool keyboard[CHIP8_KEYS];
  uint8_t sp;
  uint16_t pc;
  uint16_t index;
  uint8_t delayTimer;
  uint8_t soundTimer;

  uint16_t instruction;

 private:
  void opcode0x0();
  void opcode0x0e0();
  void opcode0x0ee();
  void opcode0x1();
  void opcode0x2();
  void opcode0x3();
  void opcode0x4();
  void opcode0x5();
  void opcode0x6();
  void opcode0x7();
  void opcode0x8();
  void opcode0x8xy1();
  void opcode0x8xy2();
  void opcode0x8xy3();
  void opcode0x8xy4();
  void opcode0x8xy5();
  void opcode0x8xy6();
  void opcode0x8xy7();
  void opcode0x8xye();
  void opcode0x9();
  void opcode0xa();
  void opcode0xb();
  void opcode0xc();
  void opcode0xd();
  void opcode0xe();
  void opcode0xex9e();
  void opcode0xexa1();
  void opcode0xf();
  void opcode0xfx07();
  void opcode0xfx0a();
  void opcode0xfx15();
  void opcode0xfx18();
  void opcode0xfx1e();
  void opcode0xfx29();
  void opcode0xfx33();
  void opcode0xfx55();
  void opcode0xfx65();
};
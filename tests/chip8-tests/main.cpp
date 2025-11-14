#include <gtest/gtest.h>

#include "chip8/chip8.hpp"
#include "chip8/loader.hpp"

using std::ios;
using std::ofstream;

TEST(Chip8, Opcode0x00e0) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x00, 0xe0};  // cls
  vector<int32_t> screen{1, 1, 1};

  cpu.setMemory(CHIP8_MEMORY_START, code);
  cpu.setVideo(0, screen);

  // act
  cpu.execute();

  // assert
  for (auto pixel : cpu.video) {
    ASSERT_EQ(pixel, 0);
  }
}

TEST(Chip8, Opcode0x00ee) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x00, 0xee};  // ret
  vector<uint16_t> addrs{0x202, 0x600, 0x1300};

  cpu.setMemory(CHIP8_MEMORY_START, code);
  cpu.setStack(addrs);
  auto sp = cpu.sp;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.sp, sp - 1);
  ASSERT_EQ(cpu.pc, addrs.back());
}

TEST(Chip8, Opcode0x1) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x12, 0x34};

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, 0x234);
}

TEST(Chip8, Opcode0x2) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x2f, 0xed};

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto sp = cpu.sp;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, 0xfed);
  ASSERT_EQ(cpu.sp, sp + 1);
  ASSERT_EQ(cpu.stack[sp], 0x202);
}

TEST(Chip8, Opcode0x3Failure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x39, 0xed};
  cpu.registers[0x9] = 0xff;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
}

TEST(Chip8, Opcode0x3Success) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x39, 0xed};
  cpu.registers[0x9] = 0xed;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 4);
}

TEST(Chip8, Opcode0x4Failure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x48, 0xed};
  cpu.registers[0x8] = 0xed;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
}

TEST(Chip8, Opcode0x4Success) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x48, 0xed};
  cpu.registers[0x8] = 0xff;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 4);
}

TEST(Chip8, Opcode0x5Failure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x58, 0xe0};
  cpu.registers[0x8] = 0xed;
  cpu.registers[0xe] = 0xff;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
}

TEST(Chip8, Opcode0x5Success) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x58, 0x70};
  cpu.registers[8] = 0xff;
  cpu.registers[7] = 0xff;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 4);
}

TEST(Chip8, Opcode0x6) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x67, 0x34};
  cpu.registers[0x7] = 0x20;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x7], 0x34);
}

TEST(Chip8, Opcode0x7) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x75, 0x34};
  cpu.registers[0x5] = 0x20;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x54);
}

TEST(Chip8, Opcode0x8xy1) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x61};
  cpu.registers[0x5] = 0x20;
  cpu.registers[0x6] = 0x40;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x60);
}

TEST(Chip8, Opcode0x8xy2) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x62};
  cpu.registers[0x5] = 0x21;
  cpu.registers[0x6] = 0x01;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x01);
}

TEST(Chip8, Opcode0x8xy3) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x63};
  cpu.registers[0x5] = 0x21;
  cpu.registers[0x6] = 0x01;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x20);
}

TEST(Chip8, Opcode0x8xy4NoOverflow) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x64};
  cpu.registers[0x5] = 0xf0;
  cpu.registers[0x6] = 0x03;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0xf3);
  ASSERT_EQ(cpu.registers[0xf], 0x0);
}

TEST(Chip8, Opcode0x8xy4Overflow) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x64};
  cpu.registers[0x5] = 0xf0;
  cpu.registers[0x6] = 0x20;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x10);
  ASSERT_EQ(cpu.registers[0xf], 0x1);
}

TEST(Chip8, Opcode0x8xy5Underflow) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x65};
  cpu.registers[0x5] = 0xf0;
  cpu.registers[0x6] = 0x03;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0xed);
  ASSERT_EQ(cpu.registers[0xf], 0x1);
}

TEST(Chip8, Opcode0x8xy5NoUnderflow) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x65};
  cpu.registers[0x5] = 0x0f;
  cpu.registers[0x6] = 0x20;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0xef);
  ASSERT_EQ(cpu.registers[0xf], 0x0);
}

TEST(Chip8, Opcode0x8xy6) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x66};
  cpu.registers[0x5] = 0x2f;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x17);
  ASSERT_EQ(cpu.registers[0xf], 0x1);
}

TEST(Chip8, Opcode0x8xy7Underflow) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x67};
  cpu.registers[0x5] = 0xf0;
  cpu.registers[0x6] = 0xf3;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x03);
  ASSERT_EQ(cpu.registers[0xf], 0x1);
}

TEST(Chip8, Opcode0x8xy7NoUnderflow) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x67};
  cpu.registers[0x5] = 0x2f;
  cpu.registers[0x6] = 0x20;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0xf1);
  ASSERT_EQ(cpu.registers[0xf], 0x0);
}

TEST(Chip8, Opcode0x8xye) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x85, 0x6e};
  cpu.registers[0x5] = 0x2f;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x5e);
  ASSERT_EQ(cpu.registers[0xf], 0x0);
}

TEST(Chip8, Opcode0x9Failure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x98, 0xe0};
  cpu.registers[0x8] = 0xed;
  cpu.registers[0xe] = 0xed;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
}

TEST(Chip8, Opcode0x9Success) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0x98, 0x70};
  cpu.registers[8] = 0xff;
  cpu.registers[7] = 0x00;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 4);
}

TEST(Chip8, Opcode0xannn) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xa5, 0x6f};

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.index, 0x56f);
}

TEST(Chip8, Opcode0xbnnn) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xb5, 0x6f};
  cpu.registers[0] = 0xf0;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.index, 0x65f);
}

TEST(Chip8, Opcode0xcxkk) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xc5, 0x6f};
  srand(42);
  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0x20);
}

TEST(Chip8, Opcode0xd) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xd5, 0x62};
  cpu.index = 0x900;
  cpu.registers[0x5] = 0x1;
  cpu.registers[0x6] = 0x1;
  vector<uint8_t> sprite{0xff};

  cpu.setMemory(CHIP8_MEMORY_START, code);
  cpu.setMemory(cpu.index, sprite);
  cpu.video[0x44] = 0xffffffff;
  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.video[0x41], 0xffffffff);
  ASSERT_EQ(cpu.video[0x42], 0xffffffff);
  ASSERT_EQ(cpu.video[0x43], 0xffffffff);
  ASSERT_EQ(cpu.video[0x44], 0x0);
  ASSERT_EQ(cpu.video[0x45], 0xffffffff);
  ASSERT_EQ(cpu.video[0x46], 0xffffffff);
  ASSERT_EQ(cpu.video[0x47], 0xffffffff);
  ASSERT_EQ(cpu.video[0x48], 0xffffffff);
  ASSERT_EQ(cpu.registers[0xf], 0x1);
}

TEST(Chip8, Opcode0xex9eFailure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xe8, 0x9e};
  cpu.registers[0x8] = 0x0a;
  cpu.keyboard[0x0a] = false;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
}

TEST(Chip8, Opcode0xex9eSuccess) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xe8, 0x9e};
  cpu.registers[0x8] = 0x0a;
  cpu.keyboard[0x0a] = true;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 4);
}

TEST(Chip8, Opcode0xexa1Failure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xe8, 0xa1};
  cpu.registers[0x8] = 0x0a;
  cpu.keyboard[0x0a] = true;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
}

TEST(Chip8, Opcode0xexa1Success) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xe8, 0xa1};
  cpu.registers[8] = 0x0a;
  cpu.keyboard[0x0a] = false;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 4);
}

TEST(Chip8, Opcode0xfx07) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x07};
  cpu.delayTimer = 0xff;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.registers[0x5], 0xff);
}

TEST(Chip8, Opcode0xfx0aFailure) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf8, 0x0a};
  cpu.registers[0x8] = 0xff;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc);
  ASSERT_EQ(cpu.registers[0x8], 0xff);
}

TEST(Chip8, Opcode0xfx0aSuccess) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf8, 0x0a};
  cpu.keyboard[0x0a] = true;

  cpu.setMemory(CHIP8_MEMORY_START, code);
  auto pc = cpu.pc;

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.pc, pc + 2);
  ASSERT_EQ(cpu.registers[0x8], 0x0a);
}

TEST(Chip8, Opcode0xfx15) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x15};
  cpu.registers[0x5] = 0xfe;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.delayTimer, 0xfe);
}

TEST(Chip8, Opcode0xfx18) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x18};
  cpu.registers[0x5] = 0xfe;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.soundTimer, 0xfe);
}

TEST(Chip8, Opcode0xfx1e) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x1e};
  cpu.registers[0x5] = 0xfe;
  cpu.index = 0x30;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.index, 0x012e);
}

TEST(Chip8, Opcode0xfx29) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x29};
  cpu.registers[0x5] = 0xb;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.index, 0x87);
}

TEST(Chip8, Opcode0xfx33) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x33};
  cpu.registers[0x5] = 0xf3;
  cpu.index = 0x900;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.memory[cpu.index + 2], 3);
  ASSERT_EQ(cpu.memory[cpu.index + 1], 4);
  ASSERT_EQ(cpu.memory[cpu.index], 2);
}

TEST(Chip8, Opcode0xfx55) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf5, 0x55};
  cpu.registers[0x0] = 0xf0;
  cpu.registers[0x1] = 0xf1;
  cpu.registers[0x2] = 0xf2;
  cpu.registers[0x3] = 0xf3;
  cpu.registers[0x4] = 0xf4;
  cpu.registers[0x5] = 0xf5;
  cpu.index = 0x900;

  cpu.setMemory(CHIP8_MEMORY_START, code);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.memory[cpu.index], cpu.registers[0x0]);
  ASSERT_EQ(cpu.memory[cpu.index + 1], cpu.registers[0x1]);
  ASSERT_EQ(cpu.memory[cpu.index + 2], cpu.registers[0x2]);
  ASSERT_EQ(cpu.memory[cpu.index + 3], cpu.registers[0x3]);
  ASSERT_EQ(cpu.memory[cpu.index + 4], cpu.registers[0x4]);
  ASSERT_EQ(cpu.memory[cpu.index + 5], cpu.registers[0x5]);
}

TEST(Chip8, Opcode0xfx65) {
  // arrange
  Chip8 cpu;
  vector<uint8_t> code{0xf7, 0x65};
  cpu.index = 0x900;
  vector<uint8_t> registres{0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
  cpu.setMemory(CHIP8_MEMORY_START, code);
  cpu.setMemory(cpu.index, registres);

  // act
  cpu.execute();

  // assert
  ASSERT_EQ(cpu.memory[cpu.index], cpu.registers[0x0]);
  ASSERT_EQ(cpu.memory[cpu.index + 1], cpu.registers[0x1]);
  ASSERT_EQ(cpu.memory[cpu.index + 2], cpu.registers[0x2]);
  ASSERT_EQ(cpu.memory[cpu.index + 3], cpu.registers[0x3]);
  ASSERT_EQ(cpu.memory[cpu.index + 4], cpu.registers[0x4]);
  ASSERT_EQ(cpu.memory[cpu.index + 5], cpu.registers[0x5]);
  ASSERT_EQ(cpu.memory[cpu.index + 5], cpu.registers[0x5]);
  ASSERT_EQ(cpu.memory[cpu.index + 6], cpu.registers[0x6]);
  ASSERT_EQ(cpu.memory[cpu.index + 7], cpu.registers[0x7]);
}

TEST(Chip8, EmulatorLoadFailure1) {
  // arrange
  Chip8 cpu;
  ROMLoader loader{};

  // act
  auto result = loader.loadROM(cpu, "invalid_rom.ch8");

  // assert
  ASSERT_EQ(result, false);
}

TEST(Chip8, EmulatorLoadFailure2) {
  // arrange
  Chip8 cpu;
  ROMLoader loader{};
  ofstream rom{"invalid_rom.ch8", ios::out | ios::binary};
  rom.close();

  // act
  auto result = loader.loadROM(cpu, "invalid_rom.ch8");

  // assert
  ASSERT_EQ(result, false);
}

TEST(Chip8, EmulatorLoadFailure3) {
  // arrange
  Chip8 cpu;
  ROMLoader loader{};
  ofstream rom{"invalid_rom.ch8", ios::out | ios::binary};
  char opcode = 0x00;
  for (auto i = 0; i < CHIP8_MEMORY_SIZE; i++) {
    rom.write(&opcode, 1);
  }
  rom.close();

  // act
  auto result = loader.loadROM(cpu, "invalid_rom.ch8");

  // assert
  ASSERT_EQ(result, false);
}

TEST(Chip8, EmulatorLoadSuccess) {
  // arrange
  Chip8 cpu;
  ROMLoader loader{};
  ofstream rom{"valid_rom.ch8", ios::out | ios::binary};
  char opcode = 0x00e0;
  for (auto i = 0; i < 8; i++) {
    rom.write(reinterpret_cast<const char*>(&opcode), 2);
  }
  rom.close();

  // act
  auto result = loader.loadROM(cpu, "valid_rom.ch8");

  // assert
  ASSERT_EQ(result, true);
}

TEST(Chip8, FontLoader) {
  // arrange
  Chip8 cpu;
  FontLoader loader{};

  // act
  loader.loadFont(cpu);

  // assert
  ASSERT_EQ(cpu.memory[CHIP8_FONTS_START], loader.getFont(0, 0));
  ASSERT_EQ(cpu.memory[CHIP8_FONTS_START + CHIP8_FONTS * CHIP8_FONT_SIZE - 1],
            loader.getFont(0xf, 0x4));
}
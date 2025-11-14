#include "chip8.hpp"

Chip8::Chip8() { reset(); }

void Chip8::reset() {
  pc = CHIP8_MEMORY_START;
  sp = 0;
  memset(memory, 0, sizeof(memory));
  memset(video, 0, sizeof(video));
  memset(keyboard, 0, sizeof(keyboard));
}

void Chip8::setMemory(uint16_t start, const vector<uint8_t>& code) {
  auto address = start;
  for (auto opcode : code) {
    memory[address] = opcode;
    address++;
  }
}

void Chip8::setVideo(uint16_t start, const vector<int32_t>& screen) {
  auto address = start;
  for (auto pixel : screen) {
    video[address] = pixel;
    address++;
  }
}

void Chip8::setStack(const vector<uint16_t>& addrs) {
  for (auto addr : addrs) {
    stack[sp] = addr;
    sp++;
  }
}

void Chip8::execute() {
  instruction = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;
  auto opcode = (instruction & 0xf000) >> 12;
  switch (opcode) {
    case 0x0:
      opcode0x0();
      break;
    case 0x1:
      opcode0x1();
      break;
    case 0x2:
      opcode0x2();
      break;
    case 0x3:
      opcode0x3();
      break;
    case 0x4:
      opcode0x4();
      break;
    case 0x5:
      opcode0x5();
      break;
    case 0x6:
      opcode0x6();
      break;
    case 0x7:
      opcode0x7();
      break;
    case 0x8:
      opcode0x8();
      break;
    case 0x9:
      opcode0x9();
      break;
    case 0xa:
      opcode0xa();
      break;
    case 0xb:
      opcode0xb();
      break;
    case 0xc:
      opcode0xc();
      break;
    case 0xd:
      opcode0xd();
      break;
    case 0xe:
      opcode0xe();
      break;
    case 0xf:
      opcode0xf();
      break;
  }
}

void Chip8::opcode0x0() {
  auto op34 = instruction & 0xff;

  switch (op34) {
    case 0xe0:
      opcode0x0e0();
      break;
    case 0xee:
      opcode0x0ee();
      break;
    default:
      break;
  }
}

void Chip8::opcode0x0e0() { memset(video, 0, sizeof(video)); }

void Chip8::opcode0x0ee() {
  sp--;
  pc = stack[sp];
}

void Chip8::opcode0x1() { pc = instruction & 0xfff; }

void Chip8::opcode0x2() {
  stack[sp] = pc;
  sp++;
  pc = instruction & 0xfff;
}

void Chip8::opcode0x3() {
  auto x = (instruction & 0x0f00) >> 8;
  auto value = instruction & 0xff;
  if (registers[x] == value) {
    pc += 2;
  }
}

void Chip8::opcode0x4() {
  auto x = (instruction & 0x0f00) >> 8;
  auto value = instruction & 0xff;
  if (registers[x] != value) {
    pc += 2;
  }
}

void Chip8::opcode0x5() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  if (registers[x] == registers[y]) {
    pc += 2;
  }
}

void Chip8::opcode0x6() {
  auto x = (instruction & 0x0f00) >> 8;
  registers[x] = instruction & 0xff;
}

void Chip8::opcode0x7() {
  auto x = (instruction & 0x0f00) >> 8;
  registers[x] += instruction & 0xff;
}

void Chip8::opcode0x8() {
  auto op4 = instruction & 0xf;
  switch (op4) {
    case 0x1:
      opcode0x8xy1();
      break;
    case 0x2:
      opcode0x8xy2();
      break;
    case 0x3:
      opcode0x8xy3();
      break;
    case 0x4:
      opcode0x8xy4();
      break;
    case 0x5:
      opcode0x8xy5();
      break;
    case 0x6:
      opcode0x8xy6();
      break;
    case 0x7:
      opcode0x8xy7();
      break;
    case 0xe:
      opcode0x8xye();
      break;
    default:
      break;
  }
}

void Chip8::opcode0x8xy1() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  registers[x] |= registers[y];
}

void Chip8::opcode0x8xy2() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  registers[x] &= registers[y];
}

void Chip8::opcode0x8xy3() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  registers[x] ^= registers[y];
}

void Chip8::opcode0x8xy4() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  int16_t sum = registers[x] + registers[y];

  if (sum > 255) {
    registers[0xf] = 1;
  } else {
    registers[0xf] = 0;
  }
  registers[x] += registers[y];
}

void Chip8::opcode0x8xy5() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  uint8_t result = registers[x] - registers[y];

  if (registers[y] < registers[x]) {
    registers[0xf] = 1;
  } else {
    registers[0xf] = 0;
  }
  registers[x] -= registers[y];
}

void Chip8::opcode0x8xy6() {
  auto x = (instruction & 0x0f00) >> 8;
  registers[0xf] = registers[x] & 0x01;
  registers[x] >>= 1;
}

void Chip8::opcode0x8xy7() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  uint8_t result = registers[x] - registers[y];

  if (registers[y] > registers[x]) {
    registers[0xf] = 1;
  } else {
    registers[0xf] = 0;
  }
  registers[x] = registers[y] - registers[x];
}

void Chip8::opcode0x8xye() {
  auto x = (instruction & 0x0f00) >> 8;
  registers[0xf] = (registers[x] & 0x80) >> 7;
  registers[x] <<= 1;
}

void Chip8::opcode0x9() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  if (registers[y] != registers[x]) {
    pc += 2;
  }
}

void Chip8::opcode0xa() { index = instruction & 0x0fff; }

void Chip8::opcode0xb() { index = registers[0] + (instruction & 0x0fff); }

void Chip8::opcode0xc() {
  auto x = (instruction & 0x0f00) >> 8;
  auto value = instruction & 0xff;
  auto r = rand() % 256;
  registers[x] = r & value;
}

void Chip8::opcode0xd() {
  auto x = (instruction & 0x0f00) >> 8;
  auto y = (instruction & 0x00f0) >> 4;
  auto n = instruction & 0x000f;

  uint8_t posx = registers[x] % CHIP8_VIDEO_WIDTH;
  uint8_t posy = registers[y] % CHIP8_VIDEO_HEIGHT;

  registers[0xF] = 0;

  for (auto row = 0; row < n; row++) {
    auto byte = memory[index + row];

    for (unsigned int col = 0; col < 8; col++) {
      auto sprite = byte & (0x80 >> col);
      auto position = (posy + row) * CHIP8_VIDEO_WIDTH + (posx + col);
      auto screen = video[position];

      if (sprite) {
        if (screen == 0xffffffff) {
          registers[0xF] = 1;
        }

        video[position] ^= 0xffffffff;
      }
    }
  }
}

void Chip8::opcode0xe() {
  auto op34 = instruction & 0xff;
  switch (op34) {
    case 0x9e:
      opcode0xex9e();
      break;
    case 0xa1:
      opcode0xexa1();
      break;
    default:
      break;
  }
}

void Chip8::opcode0xex9e() {
  auto x = (instruction & 0xf00) >> 8;
  auto key = registers[x];
  if (keyboard[key]) {
    pc += 2;
  }
}

void Chip8::opcode0xexa1() {
  auto x = (instruction & 0xf00) >> 8;
  auto key = registers[x];
  if (!keyboard[key]) {
    pc += 2;
  }
}

void Chip8::opcode0xf() {
  auto op34 = instruction & 0xff;
  switch (op34) {
    case 0x07:
      opcode0xfx07();
      break;
    case 0x0a:
      opcode0xfx0a();
      break;
    case 0x15:
      opcode0xfx15();
      break;
    case 0x18:
      opcode0xfx18();
      break;
    case 0x1e:
      opcode0xfx1e();
      break;
    case 0x29:
      opcode0xfx29();
      break;
    case 0x33:
      opcode0xfx33();
      break;
    case 0x55:
      opcode0xfx55();
      break;
    case 0x65:
      opcode0xfx65();
    default:
      break;
  }
}

void Chip8::opcode0xfx07() {
  auto x = (instruction & 0xf00) >> 8;
  registers[x] = delayTimer;
}

void Chip8::opcode0xfx0a() {
  auto x = (instruction & 0xf00) >> 8;
  for (auto i = 0; i < CHIP8_KEYS; i++) {
    if (keyboard[i]) {
      registers[x] = i;
      return;
    }
  }
  pc -= 2;
}

void Chip8::opcode0xfx15() {
  auto x = (instruction & 0xf00) >> 8;
  delayTimer = registers[x];
}

void Chip8::opcode0xfx18() {
  auto x = (instruction & 0xf00) >> 8;
  soundTimer = registers[x];
}

void Chip8::opcode0xfx1e() {
  auto x = (instruction & 0xf00) >> 8;
  index += registers[x];
}

void Chip8::opcode0xfx29() {
  auto x = (instruction & 0xf00) >> 8;
  auto digit = registers[x];
  index = CHIP8_FONTS_START + (digit * CHIP8_FONT_SIZE);
}

void Chip8::opcode0xfx33() {
  auto x = (instruction & 0xf00) >> 8;
  auto value = registers[x];
  memory[index + 2] = value % 10;
  value /= 10;
  memory[index + 1] = value % 10;
  value /= 10;
  memory[index] = value % 10;
}

void Chip8::opcode0xfx55() {
  auto x = (instruction & 0xf00) >> 8;
  for (auto i = 0; i <= x; i++) {
    memory[index + i] = registers[i];
  }
}

void Chip8::opcode0xfx65() {
  auto x = (instruction & 0xf00) >> 8;
  for (auto i = 0; i <= x; i++) {
    memory[index + i] = registers[i];
  }
}

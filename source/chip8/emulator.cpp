#include "emulator.hpp"

#include "loader.hpp"

using std::chrono::milliseconds;
using std::this_thread::sleep_for;

Chip8Emulator::Chip8Emulator(Chip8HardwareManager* hm) : hardwareManager(hm) {
  FontLoader fontLoader{};
  fontLoader.loadFont(chip8);
}

Chip8Emulator ::~Chip8Emulator() { delete hardwareManager; }

void Chip8Emulator::execute(const string& romfile) {
  ROMLoader romLoader{};
  validROM = romLoader.loadROM(chip8, romfile);
  if (validROM) {
    auto run = true;
    while (run) {
      chip8.execute();
      hardwareManager->display(chip8.video);
      run = hardwareManager->handleKeys(chip8.keyboard);

      if (chip8.delayTimer > 0) {
        chip8.delayTimer--;
      }
      if (chip8.soundTimer > 0) {
        chip8.soundTimer--;
      }

      sleep_for(milliseconds(CHIP8_DELAY));
    }
  }
}
#include "emulator.hpp"

#include "loader.hpp"

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
    }
  }
}
#include "chip8/emulator.hpp"
#include "manager/raymanager.hpp"

using std::cerr;
using std::endl;

int main(int argc, const char** argv) {
  if (argc != 2) {
    cerr << "Usage: chip8-emulator romfile" << endl;
    return 0;
  }
  RayManager* rayManager = new RayManager();
  Chip8Emulator emulator{rayManager};
  emulator.execute(argv[1]);

  return 0;
}
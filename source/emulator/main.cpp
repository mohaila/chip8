#include "chip8/emulator.hpp"
#include "manager/sdlmanager.hpp"

using std::cerr;
using std::endl;

int main(int argc, const char** argv) {
  if (argc != 2) {
    cerr << "Usage: chip8-emulator romfile" << endl;
    return 0;
  }
  SDLManager* sdlManager = new SDLManager();
  Chip8Emulator emulator{sdlManager};
  emulator.execute(argv[1]);

  return 0;
}
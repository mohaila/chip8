# Simple C++ CHIP-8 Emulator
## C++ Project
C++ project for CHIP-8 emulator:
- source/chip8 code for CHIP-8 instructions
- source/manager code for SDL display and keyboard manager
- source/emulator code for CHIP-8 emulator using previous libraries
- tests/cip8-tests code for testing chip8 library
- extern/googletest-1.17.0 

To build:
```
make build
```
For testing 
```
make test
```
For code coverage
```
make coverage
```
## Running
For testing CHIP-8 emulator, use a ROM from roms folder or your own ROM
```
./buildir/bin/chip8-emulator roms/1-chip8-logo.ch8
```
## Screenshoots
![ROM 1](./images/01.png)
![ROM 2](./images/02.png)
![ROM 3](./images/03.png)
![ROM 4](./images/04.png)
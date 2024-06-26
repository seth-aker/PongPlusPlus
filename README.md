# Pong++

A simple program written in C++ using SDL2 Libraries to play Pong

## Prerequisites

- C++17 compatible compiler
- SDL2 (2.30.4 or higher)
- SDL2_ttf
- SDL2_mixer

## Instructions

### Build command

`g++.exe -fdiagnostics-color=always -g -Wextra -Wconversion -Wsign-conversion -std=c++17 src/**.cpp main.cpp -o [Your output directory here]/main.exe -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer`

### Controls

- Right hand paddle is controlled with Arrow Keys
- Left hand paddle is controlled with W and S (in two player mode)
- Press ESC to exit/return to main menu
- Press F11 to enter full screen mode.
- Settings menu can change difficulty.

## Credits

I leaned heavily on [Chafic Najjar's](https://github.com/chaficnajjar) [21st Century Pong](https://github.com/chaficnajjar/21st-century-pong) code as a starting point because this was my first project I have written in C++.

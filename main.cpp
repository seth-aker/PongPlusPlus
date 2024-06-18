#include "src/Pong.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


int main(int argc, char* argv[]) {
    Pong pong(argc, argv);
    pong.execute();
    return 0;
}

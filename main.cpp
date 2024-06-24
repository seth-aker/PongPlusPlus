#include "main.h"
#include "src/Pong.h"
#include "src/HomeScreen.h"
#include "src/SettingsScreen.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void init() {
    bool exit = false;
    bool gameRunning = false;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    window = SDL_CreateWindow("Pong",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Settings::gameSettings.screenWidth,
        Settings::gameSettings.screenHeight,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Make sure this does not get created before TTF_Init() ever.
    HomeScreen homeScreen(exit, window, renderer);

    Pong pong(exit, window, renderer);
    //SettingsScreen settings(exit, renderer);
}


void execute() {
    while (!exit) {
        if (gameRunning) {
            pong.input();
            pong.update();
            pong.renderGameplay();
            SDL_Delay(10);
        }
        else {
            homeScreen.input();
            homeScreen.update();
            homeScreen.render();
            SDL_Delay(10);
            if (homeScreen.multiPlayerSelected || homeScreen.singlePlayerSelected) {
                gameRunning = true;
                pong.isTwoPlayerMode = homeScreen.multiPlayerSelected;
            }
        }
    }
}

void cleanup() {
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    init();
    execute();
    cleanup();
    return 0;
}

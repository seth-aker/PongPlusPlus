#include "src/Pong.h"
#include "src/HomeScreen.h"
#include "src/SettingsScreen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

bool gExitProgram;
bool gGameRunning;
bool gSettingsOpen;

SDL_Window* gWindow;
SDL_Renderer* gRenderer;

HomeScreen* homeScreen;
Pong* pong;
SettingsScreen* settingsScreen;

void init() {
    gExitProgram = false;
    gGameRunning = false;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    gWindow = SDL_CreateWindow("Pong",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Settings::gameSettings.screenWidth,
        Settings::gameSettings.screenHeight,
        SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Make sure this does not get created before TTF_Init() ever.
    homeScreen = new HomeScreen(gExitProgram, gWindow, gRenderer);
    pong = new Pong(gExitProgram, gGameRunning, gWindow, gRenderer);
    settingsScreen = new SettingsScreen(gExitProgram, gSettingsOpen, gWindow, gRenderer);
}


void execute() {
    while (!gExitProgram) {
        if (gGameRunning) {
            pong->input();
            pong->update();
            pong->renderGameplay();
            SDL_Delay(10);
        }
        else if (gSettingsOpen) {
            settingsScreen->input();
            settingsScreen->update();
            settingsScreen->render();
            SDL_Delay(10);
        }
        else {
            homeScreen->input();
            homeScreen->update();
            homeScreen->render();
            SDL_Delay(10);
            if (homeScreen->multiPlayerSelected || homeScreen->singlePlayerSelected) {
                gGameRunning = true;
                pong->isTwoPlayerMode = homeScreen->multiPlayerSelected;
            }
            else if (homeScreen->settingsSelected) {
                gSettingsOpen = true;
            }
        }
    }
}

void cleanup() {
    // Cleanup
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_CloseAudio();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    init();
    execute();
    cleanup();
    return 0;
}

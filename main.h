#ifndef MAIN_PONG_H
#define MAIN_PONG_H
#include "src/Pong.h"
#include "src/HomeScreen.h"
#include "src/SettingsScreen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

bool exit;
bool gameRunning;

SDL_Window* window;
SDL_Renderer* renderer;

HomeScreen homeScreen;
Pong pong;
SettingsScreen settingsScreen;


#endif

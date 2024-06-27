#ifndef SRC_UTILITIES_H
#define SRC_UTILITIES_H
#include "MenuButton.h"
#include <SDL2/SDL.h>
#include <string>

SDL_Texture* renderText(const std::string& message,
    const std::string& fontFile,
    SDL_Color color,
    int fontSize,
    SDL_Renderer* renderer,
    SDL_Texture* texture = nullptr);

void renderTexture(SDL_Texture* texture,
    SDL_Renderer* renderer,
    int x,
    int y,
    SDL_Rect* clip = nullptr);


void renderTriangle(SDL_Renderer* renderer,
    SDL_Color color,
    int sideLength,
    int x,
    int y,
    bool pointsRight);

bool isMouseInside(const int mouseX, const int mouseY, MenuButton* btn, const bool pointsRight = true);
#endif

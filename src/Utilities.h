#ifndef SRC_UTILITIES_H
#define SRC_UTILITIES_H

#include <SDL2/SDL.h>
#include <string>

SDL_Texture* renderText(const std::string& message
    , const std::string& fontFile
    , SDL_Color color
    , int fontSize
    , SDL_Renderer* renderer);

void renderTexture(SDL_Texture* texture
    , SDL_Renderer* renderer
    , int x
    , int y
    , SDL_Rect* prevRect = nullptr);

#endif

#include "Utilities.h"
#include <SDL2/SDL_ttf.h>
#include "MenuButton.h"

SDL_Texture* renderText(const std::string& message
    , const std::string& fontFile
    , SDL_Color color
    , int fontSize
    , SDL_Renderer* renderer)
{
    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
    SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;

}

void renderTexture(SDL_Texture* texture
    , SDL_Renderer* renderer
    , int x
    , int y
    , SDL_Rect* clip)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    if (clip != nullptr) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    else {
        SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
    }

    SDL_RenderCopy(renderer, texture, clip, &destRect);
}

bool isMouseInside(int& mouseX, int& mouseY, MenuButton* btn) {
    if (mouseX < btn->getX() || mouseX > btn->getX() + btn->WIDTH) {
        return false;
    }
    if (mouseY < btn->getY() || mouseY > btn->getY() + btn->HEIGHT) {
        return false;
    }
    return true;

}

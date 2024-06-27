#include "Utilities.h"
#include "MenuButton.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <vector>
#include <array>

SDL_Texture* renderText(const std::string& message,
    const std::string& fontFile,
    SDL_Color color,
    int fontSize,
    SDL_Renderer* renderer,
    SDL_Texture* texture)
{
    //Destroys the previous frame's texture if the texture exists to prevent memory leakage.
    if (texture) {
        SDL_DestroyTexture(texture);
    }
    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
    SDL_Surface* surface = TTF_RenderText_Blended(font, message.c_str(), color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;

}

void renderTexture(SDL_Texture* texture,
    SDL_Renderer* renderer,
    int x,
    int y,
    SDL_Rect* clip)
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

/**
* Renders isosceles triangle with a vertical side of length sideLength.
* \param renderer SDL_Renderer instance
* \param color SDL_Color
* \param sideLength length in pixels of the vertical side. Also the height of the triangle.
* \param x indicates the x coordinate position of the vertical side.
* \param y indicates the y coordinate of the top vertex of the vertical side of the triangle.
* \param pointsRight Bool indicates the direction the triangle "points". True -> right and false <- left.
*/
void renderTriangle(SDL_Renderer* renderer, SDL_Color color, int sideLength, int x, int y, bool pointsRight) {
    std::vector<SDL_Vertex> vertices = {
        // Vertex 1
        {{x, y }, color, {0,0}},
        //Vertex 2
        {{x, (y + sideLength)}, color, {0,1}},
        //Vertex 3
        {{pointsRight ? x - (sideLength * sin(60.0f)) : x + (sideLength * sin(60.0f)) , y + sideLength / 2}, color, {1,1}}
    };
    SDL_RenderGeometry(renderer, nullptr, vertices.data(), vertices.size(), NULL, 0);
}

/**
 * Checks if mouse position is within the bounds of the button.
 * \returns True when mouse is inside the button.
 * \param mouseX Int - The mouse's x coordinate
 * \param mouseY Int - The mouse's y coordinate
 * \param btn MenuButton - The button in question
 * \param pointsRight bool - When using on a triangle texture, you have to check which direction the triangle is pointing. Defaults to true.
 */
bool isMouseInside(const int mouseX, const int mouseY, MenuButton* btn, const bool pointsRight) {
    //When using on a triangle texture, you have to check which direction the triangle is pointing. Defaults to true.
    if (pointsRight) {
        if (mouseX < btn->getX() || mouseX > btn->getX() + btn->WIDTH) {
            return false;
        }
    }
    else {
        if (mouseX < btn->getX() - btn->WIDTH || mouseX > btn->getX()) {
            return false;
        }
    }


    if (mouseY < btn->getY() || mouseY > btn->getY() + btn->HEIGHT) {
        return false;
    }
    return true;

}

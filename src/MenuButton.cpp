#include "MenuButton.h"

MenuButton::MenuButton() {}

MenuButton::~MenuButton() {
    SDL_DestroyTexture(mTexture);
}

void MenuButton::setTexture(SDL_Texture* texture) {
    mTexture = texture;
    SDL_QueryTexture(mTexture, nullptr, nullptr, &WIDTH, &HEIGHT);
}

void MenuButton::setButtonPosition(int x, int y) {
    mX = x;
    mY = y;
}

int MenuButton::getX() {
    return mX;
}

int MenuButton::getY() {
    return mY;
}

SDL_Texture* MenuButton::getTexture() {
    return mTexture;
}


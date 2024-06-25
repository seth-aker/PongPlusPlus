#ifndef SRC_MENU_BUTTON_H
#define SRC_MENU_BUTTON_H

#include <SDL2/SDL.h>
#include <string>
class MenuButton {
private:
    int mX;
    int mY;
    SDL_Texture* mTexture = nullptr;
public:
    int WIDTH;
    int HEIGHT;
    MenuButton();
    ~MenuButton();
    void setButtonPosition(int x, int y);
    int getX();
    int getY();
    void setTexture(SDL_Texture* texture);
    SDL_Texture* getTexture();
    void setButtonDimensions(int h, int w);
};
#endif

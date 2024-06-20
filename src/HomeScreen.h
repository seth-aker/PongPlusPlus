#ifndef SRC_HOME_SCREEN_H
#define SRC_HOME_SCREEN_H

#include "MenuButton.h"
#include "Utilities.h"

#include <SDL2/SDL.h>

#include <string>

class HomeScreen {
private:
    const std::string fontPath;
    int mouseX;
    int mouseY;

    SDL_Renderer* renderer;
    SDL_Texture* SINGLE_PLAYER_TEXT;
    SDL_Texture* MULTI_PLAYER_TEXT;
    SDL_Texture* SETTINGS_TEXTURE;

    bool isMouseInside(int mouseX, int mouseY, MenuButton* btn);

public:
    HomeScreen(SDL_Renderer* renderer);
    ~HomeScreen();

    SDL_Texture* PONG_TEXT;

    bool singlePlayerSelected;
    bool multiPlayerSelected;
    bool settingsSelected;
    bool singlePlayerHighlighted;
    bool multiplayerHighlighted;
    bool settingsHighLighted;
    bool mouseClicked;

    MenuButton* singlePlayerBtn;
    MenuButton* multiPlayerBtn;
    MenuButton* settingsBtn;

    void input(bool& exit);
    void update();
    void render();
};

#endif

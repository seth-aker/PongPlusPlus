#ifndef SRC_HOME_SCREEN_H
#define SRC_HOME_SCREEN_H

#include "MenuButton.h"
#include "Utilities.h"
#include "Settings.h"
#include <SDL2/SDL.h>

#include <string>

class HomeScreen {
private:
    const std::string fontPath;
    int mouseX;
    int mouseY;
    bool& exitProgram;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* SINGLE_PLAYER_TEXT;
    SDL_Texture* MULTI_PLAYER_TEXT;
    SDL_Texture* SETTINGS_TEXTURE;



public:
    HomeScreen(bool& exitProgram, SDL_Window* window, SDL_Renderer* renderer);
    ~HomeScreen();

    SDL_Texture* PONG_TEXT = nullptr;

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

    void input();
    void update();
    void generateText();
    void render();
};

#endif

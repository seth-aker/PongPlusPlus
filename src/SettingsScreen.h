#ifndef SRC_SETTINGS_SCREEN_H
#define SRC_SETTINGS_SCREEN_H

#include "Settings.h"
#include "MenuButton.h"
#include <SDL2/SDL.h>
#include <string>
class SettingsScreen {
private:
    bool& exit;
    int mouseX;
    int mouseY;
    bool mouseClicked;
    const std::string fontPath;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* SETTINGS_TEXT;
    SDL_Texture* difficultyText;

    MenuButton* difficultyRight;
    int difficultyRightHighlighted;
    MenuButton* difficultyLeft;
    int difficultyLeftHighlighted;


public:
    SettingsScreen(bool& exit, SDL_Window* window, SDL_Renderer* renderer);
    ~SettingsScreen();
    void input();
    void update();
    void generateText();
    void render();


};

#endif

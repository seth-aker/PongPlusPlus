#ifndef SRC_SETTINGS_SCREEN_H
#define SRC_SETTINGS_SCREEN_H

#include "Settings.h"
#include "MenuButton.h"
#include <SDL2/SDL.h>
#include <string>
class SettingsScreen {
private:
    bool& exitProgram;
    bool& settingsOpen;
    int mouseX;
    int mouseY;
    bool mouseClicked;
    const std::string fontPath;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* SETTINGS_TEXT = nullptr;
    int settingsTextWidth;
    SDL_Texture* difficultyText = nullptr;

    MenuButton* difficultyRight;
    bool difficultyRightHighlighted;
    bool difficultyRightSelected;
    MenuButton* difficultyLeft;
    bool difficultyLeftHighlighted;
    bool difficultyLeftSelected;

public:
    const SDL_Color white{ 0xFF,0xFF,0xFF,0xFF };
    const SDL_Color yellow{ 0xFF,0xFF,0x0,0xFF };
    SettingsScreen(bool& exitProgram, bool& settingsOpen, SDL_Window* window, SDL_Renderer* renderer);
    ~SettingsScreen();
    void input();
    void update();
    void generateTextures();
    void render();


};

#endif

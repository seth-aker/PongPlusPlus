#include "SettingsScreen.h"
#include "Utilities.h"

SettingsScreen::SettingsScreen(bool& exit, SDL_Window* window, SDL_Renderer* renderer)
    : exit{ exit },
    fontPath{ "resources/fonts/Tiny5-Regular.ttf" },
    mouseClicked{ false },
    window{ window },
    renderer{ renderer },
    difficultyLeftHighlighted{ false },
    difficultyRightHighlighted{ false }
{
    SETTINGS_TEXT = renderText(
        "Settings",
        "resources/fonts/Tiny5-Regular.ttf",
        { 0xFF, 0xFF, 0xFF, 0xFF },
        96,
        renderer
    );

}

SettingsScreen::~SettingsScreen() {
    SDL_DestroyTexture(SETTINGS_TEXT);

}

void SettingsScreen::input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exit = true;
            break;
        case SDL_MOUSEMOTION || SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&mouseX, &mouseY);
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouseClicked = true;
            }
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_F11) {
                int flags = SDL_GetWindowFlags(window);
                if (flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SetWindowFullscreen(window, 0);
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
            }
            break;
        }
    }
}

void SettingsScreen::update() {

}

void SettingsScreen::generateText() {
    SDL_Color white{ 0xFF,0xFF,0xFF,0xFF };
    SDL_Color yellow{ 0xFF,0xFF,0x0,0xFF };

    difficultyRight->setTexture(renderText(
        "->",
        fontPath,
        difficultyRightHighlighted ? yellow : white,
        32,
        renderer
    ));
    difficultyLeft->setTexture(renderText(
        "<-",
        fontPath,
        difficultyLeftHighlighted ? yellow : white,
        32,
        renderer
    ));

}

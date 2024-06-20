#include "HomeScreen.h"
#include "Utilities.h"
#include "Pong.h"

HomeScreen::HomeScreen(SDL_Renderer* renderer)
    : singlePlayerSelected{ false },
    multiPlayerSelected{ false },
    settingsSelected{ false },
    mouseClicked{ false },
    fontPath{ "resources/fonts/Tiny5-Regular.ttf" },
    renderer{ renderer }
{
    singlePlayerBtn = new MenuButton{};
    multiPlayerBtn = new MenuButton{};
    settingsBtn = new MenuButton{};
    // Initial render of the home screen texts eg "Pong" and "One Player"
    render();

    // Set button positions on the screen.
    singlePlayerBtn->setButtonPosition(
        (Pong::SCREEN_WIDTH / 2) - (singlePlayerBtn->WIDTH / 2),
        (Pong::SCREEN_HEIGHT / 2));
    multiPlayerBtn->setButtonPosition(
        (Pong::SCREEN_WIDTH / 2) - (multiPlayerBtn->WIDTH / 2),
        // Set to be underneath single player button.
        (Pong::SCREEN_HEIGHT / 2 + singlePlayerBtn->HEIGHT));
    settingsBtn->setButtonPosition(
        (Pong::SCREEN_WIDTH / 2) - (settingsBtn->WIDTH / 2),
        // Set to be underneath both single and multiplayer buttons
        (Pong::SCREEN_HEIGHT / 2 + singlePlayerBtn->HEIGHT + multiPlayerBtn->HEIGHT));
}

HomeScreen::~HomeScreen() {
    SDL_DestroyTexture(PONG_TEXT);
    SDL_DestroyTexture(SINGLE_PLAYER_TEXT);
    SDL_DestroyTexture(MULTI_PLAYER_TEXT);
    SDL_DestroyTexture(SETTINGS_TEXTURE);
};

void HomeScreen::input(bool& exit) {
    SDL_Event event;
    // Reset mouse clicked flag
    mouseClicked = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit = true;
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouseX, &mouseY);
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouseClicked = true;
            }
        }
    }
}

void HomeScreen::update() {
    //Reset boolean flags.
    singlePlayerSelected = false;
    multiPlayerSelected = false;
    settingsSelected = false;

    // Set whether the mouse is hovering over each button
    singlePlayerHighlighted = isMouseInside(mouseX, mouseY, singlePlayerBtn);
    multiplayerHighlighted = isMouseInside(mouseX, mouseY, multiPlayerBtn);
    settingsHighLighted = isMouseInside(mouseX, mouseY, settingsBtn);

    // Set action flags;
    if (mouseClicked) {
        if (singlePlayerHighlighted) {
            singlePlayerSelected = true;
        }
        else if (multiplayerHighlighted) {
            multiPlayerSelected = true;
        }
        else if (settingsHighLighted) {
            settingsSelected = true;
        }
    }
}

void HomeScreen::render() {
    SDL_Color white{ 0xFF,0xFF,0xFF,0xFF };
    SDL_Color yellow{ 0xFF,0xFF,0x0,0xFF };

    PONG_TEXT = renderText(
        "PONG",
        fontPath,
        white,
        96,
        renderer);

    singlePlayerBtn->setTexture(renderText(
        "One Player",
        fontPath,
        singlePlayerHighlighted ? yellow : white,
        32,
        renderer));

    multiPlayerBtn->setTexture(renderText(
        "Two Players",
        fontPath,
        multiplayerHighlighted ? yellow : white,
        32,
        renderer));

    settingsBtn->setTexture(renderText(
        "Settings",
        fontPath,
        settingsHighLighted ? yellow : white,
        32,
        renderer));
}

bool HomeScreen::isMouseInside(int mouseX, int mouseY, MenuButton* btn) {

    if (mouseX < btn->getX() || mouseX > btn->getX() + btn->WIDTH) {
        return false;
    }
    if (mouseY < btn->getY() || mouseY > btn->getY() + btn->HEIGHT) {
        return false;
    }
    return true;

}



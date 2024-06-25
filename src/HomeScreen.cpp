#include "HomeScreen.h"
#include "Utilities.h"
#include "Pong.h"
#include "Settings.h"

HomeScreen::HomeScreen(bool& exitProgram, SDL_Window* window, SDL_Renderer* renderer)
    : singlePlayerSelected{ false },
    multiPlayerSelected{ false },
    settingsSelected{ false },
    mouseClicked{ false },
    fontPath{ "resources/fonts/Tiny5-Regular.ttf" },
    renderer{ renderer },
    window{ window },
    exitProgram{ exitProgram }
{
    singlePlayerBtn = new MenuButton{};
    multiPlayerBtn = new MenuButton{};
    settingsBtn = new MenuButton{};
    // Initial render of the home screen texts eg "Pong" and "One Player"
    generateText();
}

HomeScreen::~HomeScreen() {
    SDL_DestroyTexture(PONG_TEXT);
    SDL_DestroyTexture(SINGLE_PLAYER_TEXT);
    SDL_DestroyTexture(MULTI_PLAYER_TEXT);
    SDL_DestroyTexture(SETTINGS_TEXTURE);
};

void HomeScreen::input() {
    SDL_Event event;
    // Reset mouse clicked flag
    mouseClicked = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exitProgram = true;
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&mouseX, &mouseY);
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                mouseClicked = true;
            }
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_F11) {
                // Press F11 to enter/exitProgram fullscreen mode
                int flags = SDL_GetWindowFlags(window);
                if (flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SetWindowFullscreen(window, 0);
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE) {
                exitProgram = true;
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

void HomeScreen::generateText() {
    SDL_Color white{ 0xFF,0xFF,0xFF,0xFF };
    SDL_Color yellow{ 0xFF,0xFF,0x0,0xFF };

    // Only create the texture once.
    if (!PONG_TEXT)
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
        renderer,
        singlePlayerBtn->getTexture()));

    multiPlayerBtn->setTexture(renderText(
        "Two Players",
        fontPath,
        multiplayerHighlighted ? yellow : white,
        32,
        renderer,
        multiPlayerBtn->getTexture()));

    settingsBtn->setTexture(renderText(
        "Settings",
        fontPath,
        settingsHighLighted ? yellow : white,
        32,
        renderer,
        settingsBtn->getTexture()));

    // Set button positions on the screen.
    singlePlayerBtn->setButtonPosition(
        (Settings::gameSettings.screenWidth / 2) - (singlePlayerBtn->WIDTH / 2),
        (Settings::gameSettings.screenHeight / 2));
    multiPlayerBtn->setButtonPosition(
        (Settings::gameSettings.screenWidth / 2) - (multiPlayerBtn->WIDTH / 2),
        // Set to be underneath single player button.
        (Settings::gameSettings.screenHeight / 2 + singlePlayerBtn->HEIGHT));
    settingsBtn->setButtonPosition(
        (Settings::gameSettings.screenWidth / 2) - (settingsBtn->WIDTH / 2),
        // Set to be underneath both single and multiplayer buttons
        (Settings::gameSettings.screenHeight / 2 + singlePlayerBtn->HEIGHT + multiPlayerBtn->HEIGHT));

}

void HomeScreen::render() {
    generateText();
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int pongTextWidth;
    SDL_QueryTexture(PONG_TEXT, nullptr, nullptr, &pongTextWidth, nullptr);
    renderTexture(PONG_TEXT, renderer, Settings::gameSettings.screenWidth / 2 - pongTextWidth / 2, Settings::gameSettings.screenHeight / 5);


    // Render Single Player Text
    renderTexture(
        singlePlayerBtn->getTexture(),
        renderer,
        singlePlayerBtn->getX(),
        singlePlayerBtn->getY()
    );

    // Render Multi Player Text
    renderTexture(
        multiPlayerBtn->getTexture(),
        renderer,
        multiPlayerBtn->getX(),
        multiPlayerBtn->getY()
    );

    // Render Settings Text
    renderTexture(
        settingsBtn->getTexture(),
        renderer,
        settingsBtn->getX(),
        settingsBtn->getY()
    );
    SDL_RenderPresent(renderer);
}





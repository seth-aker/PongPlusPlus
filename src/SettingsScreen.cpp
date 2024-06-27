#include "SettingsScreen.h"
#include "Utilities.h"

SettingsScreen::SettingsScreen(bool& exitProgram, bool& settingsOpen, SDL_Window* window, SDL_Renderer* renderer)
    : exitProgram{ exitProgram }, settingsOpen{ settingsOpen },
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
    SDL_QueryTexture(SETTINGS_TEXT, NULL, NULL, &settingsTextWidth, NULL);

    difficultyLeft = new MenuButton{};
    difficultyRight = new MenuButton{};
    render();

}

SettingsScreen::~SettingsScreen() {
    SDL_DestroyTexture(SETTINGS_TEXT);
    SDL_DestroyTexture(difficultyText);

}

void SettingsScreen::input() {
    SDL_Event event;
    mouseClicked = false;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            exitProgram = true;
            break;
        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
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
            else if (event.key.keysym.sym == SDLK_ESCAPE) {
                settingsOpen = false;
            }
            break;
        }

    }
}

void SettingsScreen::update() {
    difficultyLeftSelected = false;
    difficultyRightSelected = false;
    // In order for this to be checking the correct location, the left button's position must be moved over.
    difficultyLeftHighlighted = isMouseInside(mouseX, mouseY, difficultyLeft, false);
    difficultyRightHighlighted = isMouseInside(mouseX, mouseY, difficultyRight);

    if (mouseClicked) {
        if (difficultyLeftHighlighted) {
            difficultyLeftSelected = true;
        }
        if (difficultyRightHighlighted) {
            difficultyRightSelected = true;
        }
    }

    // Typing settings over and over was becoming tedious.
    using namespace Settings;
    if (difficultyLeftSelected) {
        switch (gameSettings.selectedDifficulty)
        {
        case EASY:
            setDifficulty(IMPOSSIBLE);
            break;
        case MEDIUM:
            setDifficulty(EASY);
            break;
        case HARD:
            setDifficulty(MEDIUM);
            break;
        case IMPOSSIBLE:
            setDifficulty(HARD);
        default:
            break;
        }
    }
    if (difficultyRightSelected) {
        switch (gameSettings.selectedDifficulty)
        {
        case EASY:
            setDifficulty(MEDIUM);
            break;
        case MEDIUM:
            setDifficulty(HARD);
            break;
        case HARD:
            setDifficulty(IMPOSSIBLE);
            break;
        case IMPOSSIBLE:
            setDifficulty(EASY);
        default:
            break;
        }
    }
}

void SettingsScreen::generateTextures() {
    std::map<Settings::Difficulty, std::string> difficultyString = { {Settings::EASY, "EASY"},
                                                                {Settings::MEDIUM, "MEDIUM"},
                                                                {Settings::HARD, "HARD"},
                                                                {Settings::IMPOSSIBLE, "IMPOSSIBLE"} };
    difficultyText = renderText(
        difficultyString[Settings::gameSettings.selectedDifficulty],
        fontPath,
        white,
        32,
        renderer,
        difficultyText
    );
    int difficultyTextWidth;
    int difficultyTextHeight;

    SDL_QueryTexture(difficultyText, NULL, NULL, &difficultyTextWidth, &difficultyTextHeight);


    difficultyRight->setButtonPosition(Settings::gameSettings.screenWidth / 2 + (difficultyTextWidth), Settings::gameSettings.screenHeight / 2);
    // The button height is the length of a side of the triangle so multiplying by sin(60deg) gets you the "width" 
    difficultyRight->setButtonDimensions(difficultyTextHeight, difficultyTextHeight * -sin(60.0f));
    difficultyLeft->setButtonPosition(Settings::gameSettings.screenWidth / 2 - (difficultyTextWidth), Settings::gameSettings.screenHeight / 2);
    difficultyLeft->setButtonDimensions(difficultyTextHeight, difficultyTextHeight * -sin(60.0f));
}

void SettingsScreen::render() {
    generateTextures();
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    renderTexture(SETTINGS_TEXT, renderer, Settings::gameSettings.screenWidth / 2 - settingsTextWidth / 2, Settings::gameSettings.screenHeight / 10);

    int difficultyTextWidth;
    int difficultyTextHeight;
    SDL_QueryTexture(difficultyText, NULL, NULL, &difficultyTextWidth, &difficultyTextHeight);
    renderTexture(difficultyText, renderer, Settings::gameSettings.screenWidth / 2 - difficultyTextWidth / 2, Settings::gameSettings.screenHeight / 2);

    renderTriangle(
        renderer,
        difficultyRightHighlighted ? yellow : white,
        difficultyTextHeight,
        difficultyRight->getX(),
        difficultyRight->getY(),
        true
    );
    renderTriangle(
        renderer,
        difficultyLeftHighlighted ? yellow : white,
        difficultyTextHeight,
        difficultyLeft->getX(),
        difficultyLeft->getY(),
        false
    );
    //Prevent an extra render during initialization
    if (settingsOpen)
        SDL_RenderPresent(renderer);
}

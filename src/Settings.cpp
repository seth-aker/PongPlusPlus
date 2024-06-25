#include "Settings.h"

// Global Settings 
namespace Settings {
    bool keyboardFocus{ true };
    bool isFullScreen{ false };
    bool isMinimized{ false };

    // Default game settings;
    GameSettings gameSettings{ 480, 640, Difficulty::MEDIUM, PADDLE_SPEED / 2, 8 };

    void setDifficulty(Difficulty difficulty) {
        gameSettings.selectedDifficulty = difficulty;
        // Change the speed of the AI opponent's paddle and the ball to make it harder to score against it;
        switch (gameSettings.selectedDifficulty)
        {
        case Difficulty::EASY:
            gameSettings.aiPaddleSpeed = PADDLE_SPEED / 4;
            gameSettings.ballStartingSpeed = 6;
            break;
        case Difficulty::MEDIUM:
            gameSettings.aiPaddleSpeed = PADDLE_SPEED / 2;
            gameSettings.ballStartingSpeed = 8;
            break;
        case Difficulty::HARD:
            gameSettings.aiPaddleSpeed = PADDLE_SPEED;
            gameSettings.ballStartingSpeed = 8;
            break;
        case Difficulty::IMPOSSIBLE:
            gameSettings.aiPaddleSpeed = PADDLE_SPEED + PADDLE_SPEED / 2;
            gameSettings.ballStartingSpeed = 10;
            break;
        }
    };

    void handleWindowEvent(SDL_Event& e) {
        switch (e.window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            gameSettings.screenWidth = e.window.data1;
            gameSettings.screenHeight = e.window.data2;
            break;

            //Window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            isMinimized = true;
            break;

            //Window maximized
        case SDL_WINDOWEVENT_MAXIMIZED:
            isMinimized = false;
            break;

            //Window restored
        case SDL_WINDOWEVENT_RESTORED:
            isMinimized = false;
            break;
            //Window has keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            keyboardFocus = true;
            break;

            //Window lost keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            keyboardFocus = false;
            break;
        }
    }

}

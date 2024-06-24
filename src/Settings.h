#ifndef SRC_SETTINGS_H
#define SRC_SETTINGS_H

#include <SDL2/SDL.h>

namespace Settings {
    enum Difficulty {
        EASY,
        MEDIUM,
        HARD,
        IMPOSSIBLE
    };
    struct GameSettings {
        int screenHeight;
        int screenWidth;
        Difficulty selectedDifficulty;
        int aiPaddleSpeed;
        int ballStartingSpeed;
    };


    static const int PADDLE_SPEED = 8;
    extern bool keyboardFocus;
    extern bool isFullScreen;
    extern bool isMinimized;
    extern GameSettings gameSettings;
    void setDifficulty(Difficulty difficulty);
    void handleWindowEvent(SDL_Event& e);
};

#endif

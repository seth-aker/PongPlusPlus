#ifndef SRC_PONG_H
#define SRC_PONG_H

#include "Ball.h"
#include "HomeScreen.h"
#include "Settings.h"
#include "SettingsScreen.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <array>

class Pong {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Mix_Chunk* paddleSound;
    Mix_Chunk* wallSound;

    Ball* ball;
    Paddle* leftPaddle;
    Paddle* rightPaddle;

    std::string fontName;
    SDL_Color fontColor;

    SDL_Texture* fontRightScore = nullptr;
    SDL_Texture* fontLeftScore = nullptr;
    SDL_Texture* fontStartText = nullptr;
    SDL_Texture* fontWinnerText = nullptr;

    int leftScore;
    int rightScore;
    bool leftScoreChanged;
    bool rightScoreChanged;
    bool& gameRunning;

    bool& exitProgram;

    enum Buttons
    {
        RightPaddleUp = 0,
        RightPaddleDown,
        LeftPaddleUp,
        LeftPaddleDown
    };
    std::array<bool, 4> buttonsPressed{};

public:
    bool isTwoPlayerMode;
    Pong(bool& exitProgram, bool& gameRunning, SDL_Window* window, SDL_Renderer* renderer);
    ~Pong();
    void input();
    void update();
    void renderGameplay();

};

#endif

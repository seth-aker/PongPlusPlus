#ifndef SRC_PONG_H
#define SRC_PONG_H

#include "Ball.h"
#include "HomeScreen.h"

#include <SDL2/SDL.h>
#include <string>
#include <array>

class Pong {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    HomeScreen* homeScreen;
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
    bool gameRunning;
    bool isTwoPlayerMode;
    bool exit;

    enum Buttons
    {
        RightPaddleUp = 0,
        RightPaddleDown,
        LeftPaddleUp,
        LeftPaddleDown
    };
    std::array<bool, 4> buttonsPressed{};

public:
    static const int SCREEN_WIDTH;
    static const int SCREEN_HEIGHT;
    static const int PADDLE_SPEED;
    Pong(int argc, char* argv[]);
    ~Pong();
    void execute();
    void input();
    void update();
    void renderGameplay();
    void renderHomeScreen(HomeScreen* homeScreen);

};

#endif

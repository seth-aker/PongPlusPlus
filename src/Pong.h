#ifndef SRC_PONG_H
#define SRC_PONG_H

#include "Ball.h"


#include <SDL2/SDL.h>
#include <string>
#include <array>

class Pong {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Ball* ball;
    Paddle* leftPaddle;
    Paddle* rightPaddle;

    std::string fontName;
    SDL_Color fontColor;

    SDL_Texture* fontRightScore;
    SDL_Texture* fontLeftScore;
    SDL_Texture* fontStartText;
    SDL_Texture* fontWinnerText = nullptr;

    int leftScore;
    int rightScore;
    bool leftScoreChanged;
    bool rightScoreChanged;
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
    void render();

};

#endif

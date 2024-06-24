#include "Pong.h"
#include "Ball.h"
#include "Paddle.h"
#include "Utilities.h"
#include "Settings.h"


#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Default settings

Pong::Pong(bool exit, SDL_Window* window, SDL_Renderer* renderer)
    : leftScoreChanged{ true },
    rightScoreChanged{ true },
    gameRunning{ false },
    exit{ exit },
    window{ window },
    renderer(renderer)
{

    paddleSound = Mix_LoadWAV("resources/audio/paddleSound.wav");
    wallSound = Mix_LoadWAV("resources/audio/wallSound.wav");

    int ballCenterPosX = (Settings::gameSettings.screenWidth / 2) - (Ball::BALL_SIZE / 2);
    int ballCenterPosY = (Settings::gameSettings.screenHeight / 2) - (Ball::BALL_SIZE / 2);

    ball = new Ball{ ballCenterPosX, ballCenterPosY };
    leftPaddle = new Paddle{ 40, (Settings::gameSettings.screenHeight / 2 - Paddle::PADDLE_HEIGHT / 2) };
    rightPaddle = new Paddle{ (Settings::gameSettings.screenWidth - (40 + Paddle::PADDLE_WIDTH)),
        (Settings::gameSettings.screenHeight / 2 - Paddle::PADDLE_HEIGHT / 2) };

    fontColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    fontName = "resources/fonts/Tiny5-Regular.ttf";

    fontStartText = renderText("Press SPACE to start", fontName, fontColor, 12, renderer);
    leftScore = 0;
    rightScore = 0;

    // Array of boolean flags to determine what buttons are being pressed currently;
    buttonsPressed = { false, false, false, false };

}

Pong::~Pong() {

    SDL_DestroyTexture(fontLeftScore);
    if (fontRightScore) {
        SDL_DestroyTexture(fontRightScore);
    }
    SDL_DestroyTexture(fontStartText);
    if (fontWinnerText) {
        SDL_DestroyTexture(fontWinnerText);
    }

    Mix_FreeChunk(paddleSound);
    Mix_FreeChunk(wallSound);

}


void Pong::input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit = true;
        }
        // if keystroke down, set button pressed flag for a specific button to either pressed or not pressed.
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                gameRunning = false;
                break;
            case SDLK_SPACE:
                if (ball->status == ball->READY) {
                    ball->status = ball->LAUNCH;
                }
                break;

                // Right Player inputs
            case SDLK_UP:
                buttonsPressed[Buttons::RightPaddleUp] = true;
                break;
            case SDLK_DOWN:
                buttonsPressed[Buttons::RightPaddleDown] = true;
                break;
                //Left Player Inputs    
            case SDLK_w:
                if (isTwoPlayerMode) {
                    buttonsPressed[Buttons::LeftPaddleUp] = true;
                }
                break;
            case SDLK_s:
                if (isTwoPlayerMode) {
                    buttonsPressed[Buttons::LeftPaddleDown] = true;
                }
                break;
            case SDLK_F11:
                // Press F11 to enter/exit fullscreen mode
                int flags = SDL_GetWindowFlags(window);
                if (flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SetWindowFullscreen(window, 0);
                }
                else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
                break;

            }
        }
        else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                buttonsPressed[Buttons::RightPaddleUp] = false;
                break;
            case SDLK_DOWN:
                buttonsPressed[Buttons::RightPaddleDown] = false;
                break;
            case SDLK_w:
                if (isTwoPlayerMode) {
                    buttonsPressed[Buttons::LeftPaddleUp] = false;
                }
                break;
            case SDLK_s:
                if (isTwoPlayerMode) {
                    buttonsPressed[Buttons::LeftPaddleDown] = false;
                }
                break;

            }
        }
        Settings::handleWindowEvent(event);
    }
}

void Pong::update() {
    // Change paddle position if buttonsPressed bools are true;
    if (buttonsPressed[Buttons::RightPaddleUp]) {
        rightPaddle->setY(rightPaddle->getY() - Settings::PADDLE_SPEED);
    }
    else if (buttonsPressed[Buttons::RightPaddleDown]) {
        rightPaddle->setY(rightPaddle->getY() + Settings::PADDLE_SPEED);
    }

    if (isTwoPlayerMode) {
        if (buttonsPressed[Buttons::LeftPaddleUp]) {
            leftPaddle->setY(leftPaddle->getY() - Settings::PADDLE_SPEED);
        }
        else if (buttonsPressed[Buttons::LeftPaddleDown]) {
            leftPaddle->setY(leftPaddle->getY() + Settings::PADDLE_SPEED);
        }
    }
    // Else use AI to move the left paddle
    else {
        leftPaddle->AIMovement(ball);
    }

    // Launch Ball
    if (ball->status == ball->READY) {
        return;
    }
    else if (ball->status == ball->LAUNCH) {
        ball->launchBall();
    }

    // Update Ball Speed;
    ball->updateSpeed();

    // Check collisions
    if (ball->collidesWith(leftPaddle)) {
        ball->bouncesOff(leftPaddle);
        Mix_PlayChannel(-1, paddleSound, 0);
    }
    else if (ball->collidesWith(rightPaddle)) {
        ball->bouncesOff(rightPaddle);
        Mix_PlayChannel(-1, paddleSound, 0);
    }

    if (ball->wallCollision()) {
        ball->dy *= -1;
        Mix_PlayChannel(-1, wallSound, 0);
    }

    ball->x += ball->dx;
    ball->y += ball->dy;

    if (ball->x > Settings::gameSettings.screenWidth) {
        ++leftScore;
        leftScoreChanged = true;
        ball->reset();
    }
    else if (ball->x < 0) {
        ++rightScore;
        rightScoreChanged = true;
        ball->reset();
    }
}

void Pong::renderGameplay() {
    //Background color
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);
    // Render the net
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for (int y = 0; y < Settings::gameSettings.screenHeight; ++y)
    {
        if (y % 5)
        {
            SDL_RenderDrawPoint(renderer, Settings::gameSettings.screenWidth / 2, y);
        }
    }
    //Render Paddles 
    SDL_Rect paddleL = { leftPaddle->getX(),
        leftPaddle->getY(),
        Paddle::PADDLE_WIDTH,
        Paddle::PADDLE_HEIGHT };

    SDL_RenderFillRect(renderer, &paddleL);

    SDL_Rect paddleR = { rightPaddle->getX(),
       rightPaddle->getY(),
       Paddle::PADDLE_WIDTH,
       Paddle::PADDLE_HEIGHT };

    SDL_RenderFillRect(renderer, &paddleR);

    // Render Ball
    SDL_Rect renderedBall = { ball->x, ball->y, ball->BALL_SIZE, ball->BALL_SIZE };
    SDL_RenderFillRect(renderer, &renderedBall);

    //Render Scores
    const int scoreFontSize = 32;
    const int winnerFontSize = 24;


    if (leftScoreChanged) {
        fontLeftScore = renderText(std::to_string(leftScore)
            , fontName
            , fontColor
            , scoreFontSize
            , renderer);

        leftScoreChanged = false;
    }
    renderTexture(fontLeftScore, renderer, Settings::gameSettings.screenWidth * 4 / 10, Settings::gameSettings.screenHeight / 12);

    if (rightScoreChanged) {
        fontRightScore = renderText(std::to_string(rightScore)
            , fontName
            , fontColor
            , scoreFontSize
            , renderer);

        rightScoreChanged = false;
    }
    renderTexture(fontRightScore, renderer, Settings::gameSettings.screenWidth * 6 / 10 - scoreFontSize / 2, Settings::gameSettings.screenHeight / 12);

    if (leftScore >= 5) {
        fontWinnerText = renderText("Player 2 won!"
            , fontName
            , fontColor
            , winnerFontSize
            , renderer
        );
        renderTexture(fontWinnerText, renderer, Settings::gameSettings.screenWidth / 10 + 3, Settings::gameSettings.screenHeight / 4, nullptr);
        if (ball->status == ball->LAUNCHED) {
            leftScore = 0;
            rightScore = 0;
            leftScoreChanged = true;
            rightScoreChanged = true;
        }
    }

    if (rightScore >= 5) {
        fontWinnerText = renderText("Player 1 won!"
            , fontName
            , fontColor
            , winnerFontSize
            , renderer
        );
        renderTexture(fontWinnerText, renderer, Settings::gameSettings.screenWidth / 10 + 3, Settings::gameSettings.screenHeight / 4, nullptr);
        if (ball->status == ball->LAUNCHED) {
            leftScore = 0;
            rightScore = 0;
            leftScoreChanged = true;
            rightScoreChanged = true;
        }
    }

    if (ball->status == ball->READY) {
        int textureWidth = 0;
        int textureHeight = 0;
        SDL_QueryTexture(fontStartText, nullptr, nullptr, &textureWidth, &textureHeight);

        renderTexture(fontStartText, renderer, Settings::gameSettings.screenWidth / 2 - textureWidth / 2, Settings::gameSettings.screenHeight - 30);
    }

    SDL_RenderPresent(renderer);

}



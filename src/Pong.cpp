#include "Pong.h"
#include "Ball.h"
#include "Paddle.h"
#include "Utilities.h"

#include <SDL2/SDL_ttf.h>

const int Pong::SCREEN_HEIGHT = 480;
const int Pong::SCREEN_WIDTH = 640;
const int Pong::PADDLE_SPEED = 8;

Pong::Pong(int argc, char* argv[])
    : leftScoreChanged{ true },
    rightScoreChanged{ true },
    gameRunning{ false },
    exit{ false }
{
    exit = false;
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Pong",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int ballCenterPosX = (SCREEN_WIDTH / 2) - (Ball::BALL_SIZE / 2);
    int ballCenterPosY = (SCREEN_HEIGHT / 2) - (Ball::BALL_SIZE / 2);

    ball = new Ball{ ballCenterPosX, ballCenterPosY };
    leftPaddle = new Paddle{ 40, (SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2) };
    rightPaddle = new Paddle{ (SCREEN_WIDTH - (40 + Paddle::PADDLE_WIDTH)),
        (SCREEN_HEIGHT / 2 - Paddle::PADDLE_HEIGHT / 2) };

    TTF_Init();
    fontColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    fontName = "resources/fonts/Tiny5-Regular.ttf";

    fontStartText = renderText("Press SPACE to start", fontName, fontColor, 12, renderer);
    leftScore = 0;
    rightScore = 0;

    //Make sure this does not get created before TTF_Init() ever.
    homeScreen = new HomeScreen(renderer);
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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Pong::execute() {
    while (!exit) {
        if (gameRunning) {
            input();
            update();
            renderGameplay();
            SDL_Delay(10);
        }
        else {
            homeScreen->input(exit);
            homeScreen->update();
            homeScreen->render();
            renderHomeScreen(homeScreen);
            SDL_Delay(10);
            if (homeScreen->multiPlayerSelected || homeScreen->singlePlayerSelected) {
                gameRunning = true;
                isTwoPlayerMode = homeScreen->multiPlayerSelected;
            }
        }


    }

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
    }
}

void Pong::update() {
    isTwoPlayerMode = homeScreen->multiPlayerSelected;
    // Change paddle position if buttonsPressed bools are true;
    if (buttonsPressed[Buttons::RightPaddleUp]) {
        rightPaddle->setY(rightPaddle->getY() - PADDLE_SPEED);
    }
    else if (buttonsPressed[Buttons::RightPaddleDown]) {
        rightPaddle->setY(rightPaddle->getY() + PADDLE_SPEED);
    }

    if (isTwoPlayerMode) {
        if (buttonsPressed[Buttons::LeftPaddleUp]) {
            leftPaddle->setY(leftPaddle->getY() - PADDLE_SPEED);
        }
        else if (buttonsPressed[Buttons::LeftPaddleDown]) {
            leftPaddle->setY(leftPaddle->getY() + PADDLE_SPEED);
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
    }
    else if (ball->collidesWith(rightPaddle)) {
        ball->bouncesOff(rightPaddle);
        leftPaddle->predict(ball);
    }

    if (ball->wallCollision()) {
        ball->dy *= -1;
    }

    ball->x += ball->dx;
    ball->y += ball->dy;

    if (ball->x > SCREEN_WIDTH) {
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

    for (int y = 0; y < SCREEN_HEIGHT; ++y)
    {
        if (y % 5)
        {
            SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, y);
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
    renderTexture(fontLeftScore, renderer, SCREEN_WIDTH * 4 / 10, SCREEN_HEIGHT / 12);

    if (rightScoreChanged) {
        fontRightScore = renderText(std::to_string(rightScore)
            , fontName
            , fontColor
            , scoreFontSize
            , renderer);

        rightScoreChanged = false;
    }
    renderTexture(fontRightScore, renderer, SCREEN_WIDTH * 6 / 10 - scoreFontSize / 2, SCREEN_HEIGHT / 12);

    if (leftScore >= 5) {
        fontWinnerText = renderText("Player 2 won!"
            , fontName
            , fontColor
            , winnerFontSize
            , renderer
        );
        renderTexture(fontWinnerText, renderer, SCREEN_WIDTH / 10 + 3, SCREEN_HEIGHT / 4, nullptr);
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
        renderTexture(fontWinnerText, renderer, SCREEN_WIDTH / 10 + 3, SCREEN_HEIGHT / 4, nullptr);
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

        renderTexture(fontStartText, renderer, SCREEN_WIDTH / 2 - textureWidth / 2, SCREEN_HEIGHT - 30);
    }

    SDL_RenderPresent(renderer);

}

void Pong::renderHomeScreen(HomeScreen* homeScreen) {
    SDL_Color yellow{ 0xFF, 0xFF, 0x0, 0xFF };
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int pongTextWidth;
    SDL_QueryTexture(homeScreen->PONG_TEXT, nullptr, nullptr, &pongTextWidth, nullptr);
    renderTexture(homeScreen->PONG_TEXT, renderer, SCREEN_WIDTH / 2 - pongTextWidth / 2, SCREEN_HEIGHT / 5);


    // Render Single Player Text
    renderTexture(
        homeScreen->singlePlayerBtn->getTexture(),
        renderer,
        homeScreen->singlePlayerBtn->getX(),
        homeScreen->singlePlayerBtn->getY()
    );

    // Render Multi Player Text
    renderTexture(
        homeScreen->multiPlayerBtn->getTexture(),
        renderer,
        homeScreen->multiPlayerBtn->getX(),
        homeScreen->multiPlayerBtn->getY()
    );

    // Render Settings Text
    renderTexture(
        homeScreen->settingsBtn->getTexture(),
        renderer,
        homeScreen->settingsBtn->getX(),
        homeScreen->settingsBtn->getY()
    );
    SDL_RenderPresent(renderer);
}

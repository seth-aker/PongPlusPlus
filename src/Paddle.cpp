#include "Paddle.h"
#include "Pong.h"

const int Paddle::paddleHeight = 60;
const int Paddle::paddleWidth = 10;

Paddle::Paddle(int x, int y)
    : x(x), y(y)
{
}

int Paddle::getX() const {
    return x;
}

int Paddle::getY() const {
    return y;
}

void Paddle::setY(int y) {
    if (y < 0) {
        y = 0;
    }

    if (y + paddleHeight > Settings::gameSettings.screenHeight) {
        y = Settings::gameSettings.screenHeight - paddleHeight;
    }
    this->y = y;
}

void Paddle::AIMovement(Ball* ball) {
    // if the ball is moving left and on the left 3/5ths of the screen.
    if (ball->dx < 0 && ball->x < Settings::gameSettings.screenWidth * 3 / 5) {
        // if ball's position > paddle's position + 2
        if (ball->y + (ball->BALL_SIZE / 2) > this->getY() + paddleHeight / 2 + 2) {
            this->setY(this->getY() + Settings::gameSettings.aiPaddleSpeed);
        }
        // if ball's position < paddles position - 2
        else if (ball->y + (ball->BALL_SIZE / 2) <= this->getY() + paddleHeight / 2 - 2) {
            this->setY(this->getY() - Settings::gameSettings.aiPaddleSpeed);
        }
    }
    // Ball is moving to the right
    else if (ball->dx >= 0) {
        // Left paddle slowly moves to the center.
        if (y + paddleHeight / 2 < Settings::gameSettings.screenHeight / 2) {
            setY(this->getY() + 2);
        }
        else if (y + paddleHeight / 2 > Settings::gameSettings.screenHeight / 2) {
            setY(this->getY() - 2);
        }
    }
}

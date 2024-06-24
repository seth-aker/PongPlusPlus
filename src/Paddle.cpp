#include "Paddle.h"
#include "Pong.h"

const int Paddle::PADDLE_HEIGHT = 60;
const int Paddle::PADDLE_WIDTH = 10;


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

    if (y + PADDLE_HEIGHT > Settings::gameSettings.screenHeight) {
        y = Settings::gameSettings.screenHeight - PADDLE_HEIGHT;
    }
    this->y = y;
}

void Paddle::AIMovement(Ball* ball) {
    // if the ball is moving left and on the left 3/5ths of the screen.
    if (ball->dx < 0 && ball->x < Settings::gameSettings.screenWidth * 3 / 5) {
        // if ball's position > paddle's position + 2
        if (ball->y + (ball->BALL_SIZE / 2) > this->getY() + PADDLE_HEIGHT / 2 + 2) {
            this->setY(this->getY() + Settings::gameSettings.aiPaddleSpeed);
        }
        // if ball's position < paddles position - 2
        else if (ball->y + (ball->BALL_SIZE / 2) <= this->getY() + PADDLE_HEIGHT / 2 - 2) {
            this->setY(this->getY() - Settings::gameSettings.aiPaddleSpeed);
        }
    }
    // Ball is moving to the right
    else if (ball->dx >= 0) {
        // Left paddle slowly moves to the center.
        if (y + PADDLE_HEIGHT / 2 < Settings::gameSettings.screenHeight / 2) {
            setY(this->getY() + 2);
        }
        else if (y + PADDLE_HEIGHT / 2 > Settings::gameSettings.screenHeight / 2) {
            setY(this->getY() - 2);
        }
    }
}

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

    if (y + PADDLE_HEIGHT > Pong::SCREEN_HEIGHT) {
        y = Pong::SCREEN_HEIGHT - PADDLE_HEIGHT;
    }
    this->y = y;
}

int Paddle::predict(Ball* ball) {
    return 0;
}

void Paddle::AIMovement(Ball* ball) {

}

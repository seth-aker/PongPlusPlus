#include "Ball.h"
#include "Paddle.h"
#include "Pong.h"

#include <cmath>
#include <random>

std::random_device seed;
std::mt19937 genRandNum(seed());

const double PI = 3.14159265358979323846;
const int Ball::BALL_SIZE = 10;

Ball::Ball(int x, int y)
    : x(x)
    , y(y)
    , status(READY)
    , dx(0)
    , dy(0)
    , bounce(false)
    , speed(8)
    , angle(0.0f)
    , hits(0)

{}

void Ball::launchBall()
{
    std::uniform_int_distribution<int> dir(0, 1);
    int direction = (dir(genRandNum) ? -1 : 1);

    std::uniform_int_distribution<int> ang(-60, 60);
    angle = ang(genRandNum);

    dx = direction * speed * std::cos(angle * PI / 180.0f);
    dy = speed * std::sin(angle * PI / 180.0f);

    status = LAUNCHED;
}

void Ball::bouncesOff(Paddle* paddle) {
    if (!paddle) return;

    ++hits;
    // If ball is on the right side of the screen, make it go left and vice versa.
    int sign = (this->x > Settings::gameSettings.screenWidth / 2 ? -1 : 1);

    // Distance in pixels from the bottom of the ball to the center of the paddle
    double relativeY = ((y + BALL_SIZE / 2) - (paddle->getY() + (paddle->paddleHeight / 2)));

    // position of ball relative to the paddle, normalized to between -1 and 1 by dividing by half the hight of the paddle, then multiplied by 75deg
    angle = (((relativeY) / (paddle->paddleHeight / 2.0)) * 75.0);

    // Convert angle to Radian, find its cos() and multiply by the speed.
    dx = sign * speed * std::cos(angle * PI / 180.0f);

    dy = speed * std::sin(angle * PI / 180.0f);
}

void Ball::updateSpeed()
{
    if (hits >= 5) {
        ++speed;
        hits = 0;
    }
}

bool Ball::wallCollision()
{
    return (y + dy < 0 || y + BALL_SIZE + dy >= Settings::gameSettings.screenHeight);
}

bool Ball::collidesWith(Paddle* paddle)
{
    int ballLeft = x;
    int ballRight = x + BALL_SIZE;
    int ballTop = y;
    int ballBottom = y + BALL_SIZE;

    int paddleLeft = paddle->getX();
    int paddleRight = paddle->getX() + paddle->paddleWidth;
    int paddleTop = paddle->getY();
    int paddleBottom = paddle->getY() + paddle->paddleHeight;

    // If the edges of the ball do not intersect with the edges of the paddle return false else return true.
    if (ballLeft >= paddleRight
        || ballRight <= paddleLeft
        || ballTop >= paddleBottom
        || ballBottom <= paddleTop
        ) {
        return false;
    }
    else return true;
}

void Ball::reset() {
    x = Settings::gameSettings.screenWidth / 2 - BALL_SIZE / 2;
    y = Settings::gameSettings.screenHeight / 2;

    // Ball is fixed.
    dx = 0;
    dy = 0;
    status = READY;

    // Speed and hit counter are reset to their initial positions.
    speed = 8;
    hits = 0;
}

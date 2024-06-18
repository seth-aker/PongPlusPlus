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
    // To invert direction of ball;
    int sign = (dx <= 0 ? 1 : -1);

    // TODO: Figure out why this is necessary. 
    int relativeY = (y - paddle->getY() + BALL_SIZE);

    // TODO: Figure out what 2.14 and 75.0f represent
    angle = (2.14f * relativeY - 75.0f);

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
    return (y + dy < 0 || y + BALL_SIZE + dy >= Pong::SCREEN_HEIGHT);
}

bool Ball::collidesWith(Paddle* paddle)
{
    int ballLeft = x;
    int ballRight = x + BALL_SIZE;
    int ballTop = y;
    int ballBottom = y + BALL_SIZE;

    int paddleLeft = paddle->getX();
    int paddleRight = paddle->getX() + paddle->PADDLE_WIDTH;
    int paddleTop = paddle->getY();
    int paddleBottom = paddle->getY() + paddle->PADDLE_HEIGHT;

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
    x = Pong::SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    y = Pong::SCREEN_HEIGHT / 2;

    // Ball is fixed.
    dx = 0;
    dy = 0;
    status = READY;

    // Speed and hit counter are reset to their initial positions.
    speed = 8;
    hits = 0;
}

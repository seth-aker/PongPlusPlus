#ifndef SRC_PADDLE_H
#define SRC_PADDLE_H

class Ball;
class Paddle {
private:
    int x;
    int y;
public:
    static const int paddleHeight;
    static const int paddleWidth;

    Paddle(int x, int y);
    int getX() const;
    int getY() const;
    void setY(int y);
    void AIMovement(Ball* ball);
};

#endif

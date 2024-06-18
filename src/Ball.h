#ifndef SRC_BALL_H
#define SRC_BALL_H

class Paddle;
class Ball {
public:
    static const int BALL_SIZE;

    Ball(int x, int y);
    ~Ball() {}

    // Ball position
    int x;
    int y;

    enum Status
    {
        READY,
        LAUNCH,
        LAUNCHED
    };
    Status status;


    // Ball change in position for next frame
    int dx;
    int dy;

    // True when next frame renders ball after a collision; 
    bool bounce;

    int speed; // ball speed sqrt(dx^2 + dy^2);

    float angle; // Angle after collision with paddle.

    int hits; // Counts the number of hits with the right paddle;

    void launchBall();
    void bouncesOff(Paddle* paddle);
    void updateSpeed();
    bool wallCollision();
    bool collidesWith(Paddle* paddle);
    void reset();
};
#endif 

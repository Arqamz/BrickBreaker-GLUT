#pragma once

#include "Blocks.h"
#include "Ball.h"

class Paddle : public Blocks {
public:
    Paddle(float* color, int x, int y, int width, int height, int speed)
        : Blocks(color, x, y, width, height), speed(speed), dx(0) {}

    int getSpeed() const { return speed; }
    void setSpeed(int newSpeed) { speed = newSpeed; }
    int getDx() const { return dx; }
    void setDx(int newDx) { dx = newDx; }

    void move(int dx) {
        x += dx * speed;
    }

    void draw() override {
        DrawRoundRect(x, y, width, height, color);
    }

    void ballCollision(Ball& ball) override {

        float brickCenterX = x + width / 2;
        float brickCenterY = y + height / 2;

        // Calculate vector from brick center to ball center
        float dx = ball.getX() - brickCenterX;
        float dy = ball.getY() - brickCenterY;

        // Calculate normal vector of collision surface
        float nx = dx / (width / 2);
        float ny = dy / (height / 2);

        float horizontalV = ball.getHorizontalVelocity();
        float verticalV = ball.getVerticalVelocity();

        float dotProduct = horizontalV * nx + verticalV * ny;

        // Reflect velocity vector across the normal vector
        ball.setHorizontalVelocity(horizontalV - 2 * dotProduct * nx);
        ball.setVerticalVelocity(verticalV - 2 * dotProduct * ny);

        // Change paddle color to ball color
        setColor(ball.getColor());
    }

private:
    float speed;
    int dx;
};


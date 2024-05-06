#pragma once

#include "Blocks.h"
#include "Ball.h"

class Bricks : public Blocks {
public:
    Bricks(float* color, int x, int y, int width, int height, int lives)
        : Blocks(color, x, y, width, height), lives(lives) {}

    int getLives() const { return lives; }
    void setLives(int newLives) { lives = newLives; }

    void draw() override {
        DrawRectangle(x, y, width, height, color);
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

        // Decrement brick lives
        lives--;

        // Check if lives are zero
        if (lives == 0) {
            // Delete the brick object
            delete this;
        }

        // Change ball color to brick color
        ball.setColor(color);
    }

private:
    int lives;
};

class GreenBrick : public Bricks {
public:
    GreenBrick(int x, int y, int width, int height)
        : Bricks(green, x, y, width, height, 1) {}
};

class PinkBrick : public Bricks {
public:
    PinkBrick(int x, int y, int width, int height)
        : Bricks(pink, x, y, width, height, 2) {}
};

class BlueBrick : public Bricks {
public:
    BlueBrick(int x, int y, int width, int height)
        : Bricks(blue, x, y, width, height, 3) {}
};

class RedBrick : public Bricks {
public:
    RedBrick(int x, int y, int width, int height)
        : Bricks(red, x, y, width, height, 3) {}
};

class YellowBrick : public Bricks {
public:
    YellowBrick(int x, int y, int width, int height)
        : Bricks(yellow, x, y, width, height, 2) {}
};

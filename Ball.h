#pragma once

#include "util.h"
#include "Blocks.h"

class Ball {
private:
    float x, y;
    float verticalVelocity;
    float horizontalVelocity;
    float radius;
    float* color;

public:
    Ball(float startX, float startY, float startDX, float startDY, float ballRadius, float* ballColor) {
        x = startX;
        y = startY;
        radius = ballRadius;
        color = ballColor;
    }

    void move() {
        x += horizontalVelocity;
        y += verticalVelocity;
    }

    void draw() {
        DrawCircle(x, y, radius, color);
    }

    float getX() const {
        return x;
    }
    void setX(float newX) {
        x = newX;
    }

    float getY() const {
        return y;
    }
    void setY(float newY) {
        y = newY;
    }

    float getVerticalVelocity() const {
        return verticalVelocity;
    }

    float getHorizontalVelocity() const {
        return horizontalVelocity;
    }

    void setVerticalVelocity(float newVerticalVelocity) {
        verticalVelocity = newVerticalVelocity;
    }

    void setHorizontalVelocity(float newHorizontalVelocity) {
        horizontalVelocity = newHorizontalVelocity;
    }

    void setColor(float* newColor) {
        color = newColor;
    }

    float* getColor() const {
        return color;
    }
    
    float getRadius() const {
        return radius;
    }

};

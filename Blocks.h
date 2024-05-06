#pragma once

#include "util.h"
#include "Ball.h"

class Blocks {
public:
    Blocks(float* color, int x, int y, int width, int height)
        : color(color), x(x), y(y), width(width), height(height) {}

    float* getColor() const { return color; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setColor(float* newColor) { color = newColor; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setWidth(int newWidth) { width = newWidth; }
    void setHeight(int newHeight) { height = newHeight; }

    virtual void draw() = 0;

    virtual void ballCollision(Ball& ball) = 0;

protected:
    float* color;
    int x;
    int y;
    int width;
    int height;
};
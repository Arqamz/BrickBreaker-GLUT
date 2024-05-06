#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "util.h"
#include "util.cpp"

class Ball {
private:
    float x, y;
    float speed; // Magnitude of velocity vector
    float horizontalVelocity;
    float verticalVelocity;
    float radius;
    float* color;

public:
    Ball(float startX, float startY, float startSpeed, float startDX, float startDY, float ballRadius, float* ballColor) {
        x = startX;
        y = startY;
        speed = startSpeed;
        horizontalVelocity = startDX;
        verticalVelocity = startDY;
        radius = ballRadius;
        color = ballColor;
    }

    void move() {
        x += horizontalVelocity * speed;
        y += verticalVelocity * speed;
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

    float getSpeed() const {
        return speed;
    }

    void setSpeed(float newSpeed) {
        speed = newSpeed;
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
        if (ball.getX() + ball.getRadius() >= x && ball.getX() - ball.getRadius() <= x + width &&
            ball.getY() + ball.getRadius() >= y && ball.getY() - ball.getRadius() <= y + height) {
            ball.setVerticalVelocity(-ball.getVerticalVelocity());
            cout << lives << endl;
            ball.setColor(this->getColor());
            lives--;
        }
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

class Paddle : public Blocks {
public:
    Paddle(float* color, int x, int y, int width, int height, int speed)
        : Blocks(color, x, y, width, height), speed(speed) {}

    int getSpeed() const { return speed; }
    void setSpeed(int newSpeed) { speed = newSpeed; }

    void move(int dx) {
        x += dx * speed;
    }

    void draw() override {
        DrawRoundRect(x, y, width, height, color);
    }

    void ballCollision(Ball& ball) override {
        // Check if the ball collides with the brick
        if (ball.getX() + ball.getRadius() >= x && ball.getX() - ball.getRadius() <= x + width &&
            ball.getY() + ball.getRadius() >= y && ball.getY() - ball.getRadius() <= y + height) {
            // Reverse the vertical velocity of the ball
            ball.setVerticalVelocity(-ball.getVerticalVelocity());
            
            // Change the color of the paddle to the color of the ball
            this->setColor(ball.getColor());
        }
    }


private:
    int speed;
};

using BrickLayer = std::vector<Bricks>;

using BrickLevels = std::vector<BrickLayer>;

Paddle* paddle = nullptr;

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            paddle->move(-1);
            break;
        case 'd':
            paddle->move(1);
            break;
    }
    glutPostRedisplay();
}

void update(vector<Bricks*>& bricks, int value) {
    
    static Ball ball(250, 100, 4.0, 2, 2, 10, white);
    ball.move();

    for (auto it = bricks.begin(); it != bricks.end(); ) {
        (*it)->ballCollision(ball);
        if ((*it)->getLives() == 0) {
            it = bricks.erase(it);
        } else {
            ++it;
        }
    }

    for( auto& brick : bricks ) {
        brick->draw();
    }


    glClear(GL_COLOR_BUFFER_BIT);
    
    
    paddle->draw();
    paddle->ballCollision(ball);



    ball.draw();
    float ballX = ball.getX();
    float ballY = ball.getY( );
    float ballRadius = ball.getRadius();
    float windowWidth = 600;
    float windowHeight = 600;
    
    if (ballX - ballRadius <= 0 || ballX + ballRadius >= windowWidth) {
        ball.setHorizontalVelocity(-ball.getHorizontalVelocity());
    }

    if (ballY - ballRadius <= 0 || ballY + ballRadius >= windowHeight) {
        ball.setVerticalVelocity(-ball.getVerticalVelocity());
    }
    
    glFlush();

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    paddle = new Paddle(yellow, 200, 50, 100, 20, 20);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Brick Breaker Game");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, 600, 0, 600);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    return 0;
}

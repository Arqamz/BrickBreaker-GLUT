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



const int MAX_BRICKS = 100;
const int LEVELS = 5;

class Game {
public:
    Game() {
        paddle = new Paddle(yellow, 200, 50, 100, 20, 20);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(600, 600);
        glutCreateWindow("Brick Breaker Game");
        glClearColor(0.0, 0.0, 0.0, 1.0);
        gluOrtho2D(0, 600, 0, 600);
        glutKeyboardFunc(keyboard);

        // Create array of bricks
        brickCount = 0;

        // Add bricks to array
        bricks[brickCount++] = new GreenBrick(100, 500, 50, 20);
        bricks[brickCount++] = new PinkBrick(200, 500, 50, 20);
        bricks[brickCount++] = new BlueBrick(300, 500, 50, 20);
        bricks[brickCount++] = new RedBrick(400, 500, 50, 20);
        bricks[brickCount++] = new YellowBrick(500, 500, 50, 20);

        glutTimerFunc(0, update, 0);

        score = 0;
    }

    void startGame() {
        glutMainLoop();
    }

    static Game* instance;

private:
    Paddle* paddle;
    Blocks* bricks[MAX_BRICKS];
    int brickCount;
    int score;

    static void keyboard(unsigned char key, int x, int y) {
        if (!instance) return;

        switch (key) {
            case 'a':
                instance->paddle->move(-1);
                break;
            case 'd':
                instance->paddle->move(1);
                break;
        }
        glutPostRedisplay();
    }

    static void update(int timerId) {
        if (!instance) return;

        static Ball ball(250, 100, 4.0, 2, 2, 10, white);
        ball.move();

        for (int i = 0; i < instance->brickCount; i++) {
            instance->bricks[i]->ballCollision(ball);
            if (dynamic_cast<Bricks*>(instance->bricks[i])->getLives() == 0) {
                delete instance->bricks[i];
                for (int j = i; j < instance->brickCount - 1; j++) {
                    instance->bricks[j] = instance->bricks[j + 1];
                }
                instance->brickCount--;
                i--;
            }
        }


        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < instance->brickCount; i++) {
            instance->bricks[i]->draw();
        }
        instance->paddle->draw();
        instance->paddle->ballCollision(ball);

        ball.draw();
        float ballX = ball.getX();
        float ballY = ball.getY();
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
};

Game* Game::instance = nullptr;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    Game game;
    Game::instance = &game;
    game.startGame();
    return 0;
}
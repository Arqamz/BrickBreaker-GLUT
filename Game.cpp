#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

#include "util.h"
#include "util.cpp"

using namespace std;

class Ball {
private:
    float x, y;
    float speed;
    float horizontalVelocity;
    float verticalVelocity;
    float radius;
    float* color;

public:
    Ball() {
        x = 300;
        y = 100;
        speed = 5;
        horizontalVelocity = 1;
        verticalVelocity = 1;
        radius = 10;
        color = white;
    }

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
        if (ball.getX() + ball.getRadius() >= x && ball.getX() - ball.getRadius() <= x + width &&
            ball.getY() + ball.getRadius() >= y && ball.getY() - ball.getRadius() <= y + height) {
            ball.setVerticalVelocity(-ball.getVerticalVelocity());
            this->setColor(ball.getColor());
        }
    }


private:
    int speed;
};




























class Game {
public:
    Game() : ballCount(1), balls(new Ball[10]) {
        cout << "Game constructor called." << endl;

        paddle = new Paddle(yellow, 200, 50, 100, 10, 40);

        for (int i = 0; i < ballCount; i++) {
            cout << "Ball " << i+1 << " information:" << endl;
            cout << "X: " << balls[i].getX() << endl;
            cout << "Y: " << balls[i].getY() << endl;
            cout << "Vertical Velocity: " << balls[i].getVerticalVelocity() << endl;
            cout << "Horizontal Velocity: " << balls[i].getHorizontalVelocity() << endl;
            cout << "Speed: " << balls[i].getSpeed() << endl;
            cout << "Color: (" << balls[i].getColor()[0] << ", " << balls[i].getColor()[1] << ", " << balls[i].getColor()[2] << ")" << endl;
            cout << "Radius: " << balls[i].getRadius() << endl;
            cout << endl;
        }

        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(600, 600);
        glutCreateWindow("Brick Breaker Game");
        glClearColor(0.0, 0.0, 0.0, 1.0);
        gluOrtho2D(0, 600, 0, 600);
        glutKeyboardFunc(keyboard);

        brickCount = 0;
        lives = 3;
        level = 1;

        int brickWidth = 50;
        int brickHeight = 20;
        int startX = 100;
        int startY = 500;

        for (int row = 0; row < 2; row++) {
            for (int col = 0; col < 4; col++) {
                brickCount++;
                cout << "Brick count: " << brickCount << endl;
                int randomColor = rand() % 5 + 1;
                switch (randomColor) {
                    case 1:
                        cout << "Green Brick created." << endl;
                        bricks[brickCount] = new GreenBrick(startX + col * brickWidth, startY - row * brickHeight, brickWidth, brickHeight);
                        break;
                    case 2:
                        cout << "Pink Brick created." << endl;
                        bricks[brickCount] = new PinkBrick(startX + col * brickWidth, startY - row * brickHeight, brickWidth, brickHeight);
                        break;
                    case 3:
                        cout << "Blue Brick created." << endl;
                        bricks[brickCount] = new BlueBrick(startX + col * brickWidth, startY - row * brickHeight, brickWidth, brickHeight);
                        break;
                    case 4:
                        cout << "Red Brick created." << endl;
                        bricks[brickCount] = new RedBrick(startX + col * brickWidth, startY - row * brickHeight, brickWidth, brickHeight);
                        break;
                    case 5:
                        cout << "Yellow Brick created." << endl;
                        bricks[brickCount] = new YellowBrick(startX + col * brickWidth, startY - row * brickHeight, brickWidth, brickHeight);
                        break;
                }
            }
        }

        glutTimerFunc(0, update, 0);

        score = 0;
    }

    void startGame() {
        cout << "Game started." << endl;
        glutMainLoop();
    }

    static Game* instance;

private:
    Paddle* paddle;
    Blocks* bricks[10];
    int brickCount;
    int score;
    int lives;
    int level;
    Ball* balls;
    int ballCount; 

    // void addBall(Ball& newBall) {
    //     cout << "Adding ball." << endl;
    //     Ball* temp = new Ball[ballCount + 1];
    //     for (int i = 0; i < ballCount; ++i) {
    //         temp[i] = balls[i];
    //     }
    //     temp[ballCount] = newBall;
    //     delete[] balls;
    //     balls = temp;
    //     ++ballCount;
    // }

    // void increasePaddleSize() {
    //     cout << "Increasing paddle size." << endl;
    //     int currentWidth = instance->paddle->getWidth();
    //     instance->paddle->setWidth(currentWidth + 20);
    // }

    // void reducePaddleSize() {
    //     cout << "Reducing paddle size." << endl;
    //     int currentWidth = instance->paddle->getWidth();
    //     if (currentWidth > 20) {
    //         instance->paddle->setWidth(currentWidth - 20);
    //     }
    // }

    // void slowDownBallSpeed() {
    //     cout << "Slowing down ball speed." << endl;
    //     for (int i = 0; i < ballCount; i++) {
    //         float currentSpeed = balls[i].getSpeed();
    //         balls[i].setSpeed(currentSpeed / 2);
    //     }
    // }

    // void increaseBallSpeed() {
    //     cout << "Increasing ball speed." << endl;
    //     for (int i = 0; i < ballCount; i++) {
    //         float currentSpeed = balls[i].getSpeed();
    //         balls[i].setSpeed(currentSpeed * 2);
    //     }
    // }

    // void addExtraBalls() {
    //     cout << "Adding extra balls." << endl;
    //     Ball newBall1 = balls[0];
    //     Ball newBall2 = balls[0];
    //     addBall(newBall1);
    //     addBall(newBall2);
    // }

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

        for (int i = 0; i < instance->ballCount; i++) {
            instance->balls[i].move();
            cout << "Ball " << i+1 << " moved." << endl;
        }

        cout << "Check collision with Ball\n";
        for (int i = 0; i < instance->brickCount; i++) {
            for (int j = 0; j < instance->ballCount; j++) {
                if (instance->bricks[i]) {
                    instance->bricks[i]->ballCollision(instance->balls[j]);
                }
            }
            if (instance->bricks[i] && dynamic_cast<Bricks*>(instance->bricks[i])->getLives() == 0) {
                delete instance->bricks[i];
                for (int j = i; j < instance->brickCount - 1; j++) {
                    instance->bricks[j] = instance->bricks[j + 1];
                }
                instance->brickCount--;
                i--;
                cout << "Brick " << i+1 << " destroyed." << endl;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < instance->brickCount; i++) {
            if (instance->bricks[i]) {
                instance->bricks[i]->draw();
                cout << "Brick " << i+1 << " drawn." << endl;
            }
        }

        cout << "Check paddle collision with balls" << endl;
        if (instance == nullptr) {
            cout << "Error: Game instance is null." << endl;
        } else {
            if (instance->paddle == nullptr) {
                cout << "Error: Paddle instance is null." << endl;
            } else {
                for (int i = 0; i < instance->ballCount; i++) {
                    if (i >= 10) {
                        cout << "Error: Index " << i << " is out of bounds for balls array." << endl;
                        break;
                    }
                    if (instance->balls[i].getSpeed()) {
                        instance->paddle->ballCollision(instance->balls[i]);
                        cout << "Ball " << i+1 << " collided with paddle." << endl;
                    } else {
                        cout << "Error: Ball " << i+1 << " is not valid." << endl;
                    }
                }
            }
        }


        for(int i=0;i<instance->lives;i++){
            DrawCircle(20 + i*20, 580, 5, white);
            cout << "Life " << i+1 << " drawn." << endl;
        }

        instance->paddle->draw();
        cout << "Paddle drawn." << endl;
        for (int i = 0; i < instance->ballCount; i++) {
            instance->balls[i].draw(); // Draw all balls
            cout << "Ball " << i+1 << " drawn." << endl;
        }

        float ballX, ballY, ballRadius, windowWidth, windowHeight;
        for (int i = 0; i < instance->ballCount; i++) {
            ballX = instance->balls[i].getX();
            ballY = instance->balls[i].getY();
            ballRadius = instance->balls[i].getRadius();
            windowWidth = 600;
            windowHeight = 600;

            if (ballX - ballRadius <= 0 || ballX + ballRadius >= windowWidth) {
                instance->balls[i].setHorizontalVelocity(-instance->balls[i].getHorizontalVelocity());
                cout << "Ball " << i+1 << " changed horizontal velocity." << endl;
            }

            if (ballY - ballRadius <= 0 || ballY + ballRadius >= windowHeight) {
                instance->balls[i].setVerticalVelocity(-instance->balls[i].getVerticalVelocity());
                cout << "Ball " << i+1 << " changed vertical velocity." << endl;
            }

            if (ballY - ballRadius <= 0) {
                instance->lives--;
                cout << "Life lost." << endl;
            }
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
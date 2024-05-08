class Droppables {
protected:
    int x;
    int y;

public:
    Droppables(int startX, int startY) : x(startX), y(startY) {}

    void move() {
        y += 10;
    }

    virtual void draw() = 0;
};

class Droppable1 : public Droppables {
public:
    Droppable1(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        DrawCircle(x, y, radius, color);
    }
};

class Droppable2 : public Droppables {
public:
    Droppable2(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        DrawSquare(x, y, size, color);
    }
};

class Droppable3 : public Droppables {
public:
    Droppable3(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        DrawTriangle(x1, y1, x2, y2, x3, y3, color);
    }
};

class Droppable4 : public Droppables {
public:
    Droppable4(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        DrawRectangle(x, y, width, height, color);
    }
};

class Droppable5 : public Droppables {
public:
    Droppable5(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        DrawRoundRect(x, y, width, height, color, radius);
    }
};

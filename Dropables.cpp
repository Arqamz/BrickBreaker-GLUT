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
        // Code for drawing Droppable1
    }
};

class Droppable2 : public Droppables {
public:
    Droppable2(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        // Code for drawing Droppable2
    }
};

class Droppable3 : public Droppables {
public:
    Droppable3(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        // Code for drawing Droppable3
    }
};

class Droppable4 : public Droppables {
public:
    Droppable4(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        // Code for drawing Droppable4
    }
};

class Droppable5 : public Droppables {
public:
    Droppable5(int startX, int startY) : Droppables(startX, startY) {}
    void draw() override {
        // Code for drawing Droppable5
    }
};
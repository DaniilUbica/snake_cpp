#pragma once

#include <iostream>

#include "Globals.cpp"

enum Direction {
    LEFT, RIGHT, UP, DOWN
};

struct Position {
    int x, y;
};

class Snake {
private:
    bool canLeft = true, canRight = true, canUp = true, canDown = false;

    int length;
    Position snakeCellPos[1000];
    Direction snakeDirection;

public:
    Snake(int length, Direction direction);
    void toStart();
    void move(Field& f, char field[FIELD_HEIGHT][FIELD_WIDTH + 1]);
    void plusCell();
    bool isGameOver(Field& f);
};
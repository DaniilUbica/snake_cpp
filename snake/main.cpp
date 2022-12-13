#include <iostream>
#include <Windows.h>
#include <ctime>

#include "Field.h"
#include "Snake.h"
#include "Globals.cpp"

int main()
{
    srand(time(NULL));
    setCursorVisible(false);

    Field f;
    Snake snake(1, UP);

    f.setWalls('#');

    snake.toStart();

    f.spawnApple();

    while (true) {

        if (snake.isGameOver(f)) {
            break;
        }
        snake.move(f, f.field);
        f.show();

		Sleep(GAME_SPEED);
    }
}

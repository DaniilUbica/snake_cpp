#include <Windows.h>
#include <fstream>

#include "Field.h"
#include "Snake.h"
#include "Globals.cpp"

Snake::Snake(int length, Direction direction) {
	this->length = length;
	snakeDirection = direction;
}

void Snake::toStart() {
	for (int i = 0; i < length; i++) {
		snakeCellPos[i].x = 0;
		snakeCellPos[i].y = 0;
	}

	length = 1;

	snakeCellPos[0].x = FIELD_WIDTH / 2;
	snakeCellPos[0].y = FIELD_HEIGHT / 2;

	goToCoords(snakeCellPos[0].x, snakeCellPos[0].y);
	putchar('O');
}

void Snake::move(Field& f, char field[FIELD_HEIGHT][FIELD_WIDTH + 1]) {
	if (GetAsyncKeyState('W') && canUp) {
		snakeDirection = UP;
		canLeft = canRight = true;
		canDown = false;
	}
	if (GetAsyncKeyState('A') && canLeft) {
		snakeDirection = LEFT;
		canRight = false;
		canDown = canUp = true;
	}
	if (GetAsyncKeyState('D') && canRight) {
		snakeDirection = RIGHT;
		canLeft = false;
		canDown = canUp = true;
	}
	if (GetAsyncKeyState('S') && canDown) {
		snakeDirection = DOWN;
		canLeft = canRight = true;
		canUp = false;
	}

	field[snakeCellPos[length - 1].y][snakeCellPos[length - 1].x] = ' ';

	for (int i = length; i > 0; i--) {
		snakeCellPos[i] = snakeCellPos[i - 1];
	}

	switch (snakeDirection) {
	case UP:
		snakeCellPos[0].y = snakeCellPos[0].y - 1;
		break;
	case DOWN:
		snakeCellPos[0].y = snakeCellPos[0].y + 1;
		break;
	case LEFT:
		snakeCellPos[0].x = snakeCellPos[0].x - 1;
		break;
	case RIGHT:
		snakeCellPos[0].x = snakeCellPos[0].x + 1;
		break;
	}

	if (field[snakeCellPos[0].y][snakeCellPos[0].x] == '*') {
		plusCell();
		f.points++;
		f.needSpawn = true;
		f.spawnApple();
	}

	field[snakeCellPos[0].y][snakeCellPos[0].x] = 'O';

	if (length > 1) {
		field[snakeCellPos[1].y][snakeCellPos[1].x] = 'o';
	}
}

void Snake::plusCell() {
	snakeCellPos[length].x = snakeCellPos[length - 1].x;
	snakeCellPos[length].y = snakeCellPos[length - 1].y;

	length++;
}

bool Snake::isGameOver (Field& f)
{

	bool isGameOver = false;
	std::fstream record("record.txt");
	uint16_t temp;
	record >> temp;
	record.close();

	std::fstream max_p("record.txt");

	if (snakeCellPos[0].x <= 0 || snakeCellPos[0].x >= FIELD_WIDTH - 1 || snakeCellPos[0].y <= 0 || snakeCellPos[0].y >= FIELD_HEIGHT - 1) {
		if (temp < f.points) {
			f.max_points = f.points;
			max_p << f.max_points;
		}
		isGameOver = true;
	}

	for (int i = 4; i < length; i++) {
		if (snakeCellPos[0].x == snakeCellPos[i].x && snakeCellPos[0].y == snakeCellPos[i].y) {
			if (temp < f.points) {
				f.max_points = f.points;
				max_p << f.max_points;
			}
			isGameOver = true;
		}
	}
	max_p.close();
	return isGameOver;
}


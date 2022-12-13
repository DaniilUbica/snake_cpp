#include <iostream>
#include <Windows.h>
#include <ctime>
#include <fstream>

#include "Field.h"
#include "Globals.cpp"

void Field::setWalls(char ch) {
	for (uint8_t i = 0; i < FIELD_HEIGHT; i++) {
		for (uint8_t j = 0; j < FIELD_WIDTH; j++) {
			if (i == 0 || i == FIELD_HEIGHT - 1 || j == 0 || j == FIELD_WIDTH - 1) {
				field[i][j] = ch;
			}
			else {
				field[i][j] = ' ';
			}
		}
		field[i][FIELD_WIDTH] = '\0';
	}
}

void Field::show() {
	std::fstream record("record.txt");
	record >> max_points;

	std::cout << " your points: " << " " << points << "\n";
	std::cout << " your record: " << " " << max_points << " ";
	goToCoords(0, 0);
	for (uint8_t i = 0; i < FIELD_HEIGHT; i++) {
		std::cout << field[i] << "\n";
	}
	record.close();
}

void Field::spawnApple() {
	int x = rand() % (FIELD_WIDTH - 2) + 1;
	int y = rand() % (FIELD_HEIGHT - 2) + 1;

	bool isSpawn = false;
	while (!isSpawn && needSpawn) {
		if (x % 1 == 0) {
			isSpawn = true;
		}
		if (field[y][x] == 'O' || field[y][x] == 'o') {
			isSpawn = false;
		}
		int x = rand() % (FIELD_WIDTH - 2) + 1;
		needSpawn = false;
	}
	field[y][x] = '*';
}

void goToCoords(uint8_t x, uint8_t y) {
	COORD pos = { x, y };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
}

void setCursorVisible(bool visible) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(handle, &cursorInfo);
}


#pragma once

#include <iostream>

#include "Globals.cpp"

struct Field {
	char field[FIELD_HEIGHT][FIELD_WIDTH + 1];

	bool needSpawn = true;

	uint16_t points = 0, max_points;

	void setWalls(char ch);

	void show();

	void spawnApple();
};

void goToCoords(uint8_t x, uint8_t y);

void setCursorVisible(bool visible);

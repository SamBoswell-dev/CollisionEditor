#pragma once
#include "raylib.h"

class Ball {
private:
	Vector2 position;
	float radius;
	float horizontalSpeed;
	float verticalSpeed;
	bool isTravelingRight;
	bool isTravelingDown;
	Color color;
	Sound seth;
public:
	Ball();
	void Draw();
	void Move();
private:
	bool CheckBounds(); // returns true if detects out of bounds
};
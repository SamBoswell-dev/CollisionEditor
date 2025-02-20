#include <iostream>
#include "raylib.h"
#include "Ball.h"

int main()
{
	Color backgroundColor = { 108, 153, 173, 255 };

	InitWindow(800, 800, "My Template");
	InitAudioDevice();
	SetTargetFPS(60);

	Ball ball;
	

	while (!WindowShouldClose())
	{
		ball.Move();

		BeginDrawing();
		ClearBackground(backgroundColor);
		ball.Draw();
		EndDrawing();
	}
	CloseWindow();
}
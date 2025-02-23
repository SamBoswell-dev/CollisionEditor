#include <iostream>
#include "raylib.h"
#include "SceneManager/SceneManager.h"

int main()
{
	Color backgroundColor = { 108, 153, 173, 255 };

	InitWindow(400, 400, "Collision Editor");
	InitAudioDevice();
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);
	

	SceneManager sceneManager;

	while (!WindowShouldClose())
	{
		sceneManager.Update();
		
		BeginDrawing();
		sceneManager.Draw();
		EndDrawing();
	}
	CloseWindow();
}
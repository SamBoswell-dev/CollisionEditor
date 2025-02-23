#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class SceneManager;

class Application
{
public:
	std::vector<Rectangle> colliders;
private:
	bool shouldShowFilePicker;
	std::string selectedJsonFile;
	std::string selectedPngFile;
	Texture2D tileSet;
	int scaleValue;
	bool scaleEdit;
	SceneManager* sceneManager;
	Vector2 mousePosition;
	bool isMouseHeld;
public:
	Application(SceneManager* sceneManager);
	~Application();
	void Update();
	void Draw();
private:
	char* ReadFile(const char* filename);
	void DrawTilemap(const char* jsonFile, Texture2D tileset, int tileSize, float scale);
};


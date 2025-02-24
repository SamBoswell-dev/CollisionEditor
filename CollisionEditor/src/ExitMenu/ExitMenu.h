#pragma once
#include <vector>
#include "raygui.h"
#include <string>

class ExitMenu
{
public:

private:
	std::vector<Rectangle> colliders;
	Rectangle panelBounds;
	Rectangle contentBounds;
	Vector2 scrollOffset;
	Vector2 viewOffset;
	Rectangle view;
	int collidersCount;
	std::vector<std::string> messages;
	std::string selectedSaveFile;
public:
	ExitMenu(std::vector<Rectangle> colliders);
	void Update();
	void Draw();
};


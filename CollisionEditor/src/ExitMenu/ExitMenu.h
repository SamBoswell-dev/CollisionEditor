#pragma once
#include <vector>
#include "raygui.h"

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
public:
	ExitMenu(std::vector<Rectangle> colliders);
	void Update();
	void Draw();
};


#pragma once

class SceneManager;

class MainMenu
{
public:

private:
	SceneManager* sceneManager;
	int wantedWidth;
	int wantedHeight;
	bool widthEdit;
	bool heightEdit;
public:
	explicit MainMenu(SceneManager* sceneManager);
	void Draw();
};


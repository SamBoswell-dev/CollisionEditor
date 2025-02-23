#pragma once
#include <memory>

class MainMenu;
class Application;
class ExitMenu;

enum ActiveScene {
	MAIN_MENU,
	APPLICATION,
	EXIT_MENU
};

class SceneManager {
public:

private:
	std::unique_ptr<MainMenu> mainMenu = nullptr;
	std::unique_ptr<Application> application = nullptr;
	std::unique_ptr<ExitMenu> exitMenu = nullptr;
	ActiveScene activeScene;
public:
	SceneManager();
	~SceneManager();
	void Update();
	void Draw();
	void SwitchScene(ActiveScene newScene);
private:

};
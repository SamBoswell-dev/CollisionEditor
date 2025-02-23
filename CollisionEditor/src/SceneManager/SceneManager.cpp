#include "SceneManager.h"
#include "../MainMenu/MainMenu.h"
#include "../Application.h"
#include "../ExitMenu/ExitMenu.h"

SceneManager::SceneManager()
	: activeScene(MAIN_MENU)
{
	mainMenu = std::make_unique<MainMenu>(this);
}

SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{
	if (activeScene == APPLICATION)
	{
		application->Update();
	}

	if (activeScene == EXIT_MENU)
	{
		exitMenu->Update();
	}
}

void SceneManager::Draw()
{
	switch (activeScene)
	{
	case MAIN_MENU:
		mainMenu->Draw();
		break;
	case APPLICATION:
		application->Draw();
		break;
	case EXIT_MENU:
		exitMenu->Draw();
		break;
	}
}

void SceneManager::SwitchScene(ActiveScene newScene)
{
	switch (newScene)
	{
	case APPLICATION:
		mainMenu = nullptr;
		application = std::make_unique<Application>(this);
		activeScene = APPLICATION;
		break;
	case MAIN_MENU:
		application = nullptr;
		mainMenu = std::make_unique<MainMenu>(this);
		activeScene = MAIN_MENU;
		break;
	case EXIT_MENU:
		exitMenu = std::make_unique <ExitMenu>(application->colliders);
		application = nullptr;
		activeScene = EXIT_MENU;
		break;

	}
}
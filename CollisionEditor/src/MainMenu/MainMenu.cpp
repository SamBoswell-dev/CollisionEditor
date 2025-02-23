#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "style_dark.h"
#include "MainMenu.h"
#include "../SceneManager/SceneManager.h"
#include <iostream>

MainMenu::MainMenu(SceneManager* sceneManager)
	: sceneManager(sceneManager), wantedWidth(1920), wantedHeight(1080), widthEdit(false), heightEdit(false)
{
	GuiLoadStyleDark();
}

void MainMenu::Draw()
{
	ClearBackground(DARKGRAY);

	GuiPanel({ 0, 0, 400, 400 }, "");
	if (GuiValueBox({ 176, 144, 120, 24 }, "Width", &wantedWidth, 0, 3000, widthEdit)) widthEdit = !widthEdit;
	if (GuiValueBox({ 176, 176, 120, 24 }, "Height", &wantedHeight, 0, 2000, heightEdit)) heightEdit = !heightEdit;
	if (GuiButton({ 96, 216, 200, 56 }, "Create Canvas"))
	{
		if (wantedWidth > 5 && wantedHeight > 5)
		{
			SetWindowSize(wantedWidth, wantedHeight);
			SetWindowPosition(100, 100);
			sceneManager->SwitchScene(APPLICATION);
		}
	}
	GuiGroupBox({ 80, 104, 248, 200 }, "New Canvas");

}
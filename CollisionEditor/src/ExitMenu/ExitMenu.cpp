#include "ExitMenu.h"
#include "tinyfiledialogs.h"
#include <fstream>

ExitMenu::ExitMenu(std::vector<Rectangle> colliders)
	: colliders(colliders), scrollOffset({ 0, 0 }), viewOffset({ 0, 0}), panelBounds({ 50, 50, 900, 800 }), contentBounds({ 0, 0, 1100, 1000 }), view({ 0, 0, panelBounds.width - 20, panelBounds.height - 20 }), selectedSaveFile("")
{
	// Eliminate the colliders with no size
	for (int i = 0; i < colliders.size(); i++)
	{
		if (colliders[i].height < 1 || colliders[i].width < 1)
		{
			colliders.erase(colliders.begin() + i);
			i--;
		}
	}

	collidersCount = colliders.size();


	messages.push_back("// Generated Colliders");
	messages.push_back("std::vector<Rectangle> colliders;");
	
	for (auto& i : colliders)
	{
		std::string string = "colliders.push_back({ " + std::to_string(static_cast<int>(i.x)) + ", " + std::to_string(static_cast<int>(i.y)) + ", " + std::to_string(static_cast<int>(i.width)) + ", " + std::to_string(static_cast<int>(i.height)) + " });";
		messages.push_back(string);
	}
}

void ExitMenu::Update()
{

}

void ExitMenu::Draw()
{
	ClearBackground(DARKGRAY);
	GuiScrollPanel(panelBounds, "Test text", contentBounds, &scrollOffset, &view);
	BeginScissorMode(panelBounds.x, panelBounds.y, panelBounds.width, panelBounds.height);

	// Draw multiple lines of text inside the scroll panel
	for (int i = 1; i < messages.size() + 1; i++) {
		DrawText(TextFormat(messages[i - 1].c_str()),
			panelBounds.x + 10,                      // Fixed X position
			panelBounds.y + 10 + (i * 20) + scrollOffset.y,  // Scroll Y position
			20, DARKGRAY);
	}
	EndScissorMode();



	if (GuiButton({ 50, 900, 250, 50 }, "Export code"))
	{
		const char* filterPatterns[] = { "*.cpp" };
		const char* filePath = tinyfd_saveFileDialog("Save cpp file", "", 1, filterPatterns, false);

		if (filePath)
		{
			std::ofstream file(filePath);
			if (file)
			{
				for (auto& i : messages)
				{
					file << i << "\n";
					selectedSaveFile = filePath;
				}
					file.close();
			}
		}

	}

	GuiLabel({ 50, 925, static_cast<float>(MeasureText(selectedSaveFile.c_str(), 20)), 20 }, selectedSaveFile.c_str());

}

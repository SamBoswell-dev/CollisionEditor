#include "Application.h"
#include "raygui.h"
#include "tinyfiledialogs.h"
#include "cJSON.h"
#include <iostream>
#include <string>

#include "SceneManager/SceneManager.h"

Application::Application(SceneManager* sceneManager)
	: shouldShowFilePicker(true), selectedJsonFile(""), selectedPngFile(""), scaleValue(1), scaleEdit(false), sceneManager(sceneManager), mousePosition({ 0, 0 }), colliders({}), isMouseHeld(false)
{
	//selectedJsonFile = "C:\\CppDev\\BounceArena\\bin\\Debug-windows-x86\\BounceArena\\Levels\\Map1.json";
	//tileSet = LoadTexture("C:\\CppDev\\BounceArena\\bin\\Debug-windows-x86\\BounceArena\\Levels\\Graybox_16px.png");
}

Application::~Application()
{

}

void Application::Update()
{
	mousePosition = GetMousePosition();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		colliders.emplace_back();
		colliders.back().x = GetMousePosition().x;
		colliders.back().y = GetMousePosition().y;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		colliders.back().width = GetMousePosition().x - colliders.back().x;
		colliders.back().height = GetMousePosition().y - colliders.back().y;
	}

	if (IsKeyPressed(KEY_ESCAPE))
		sceneManager->SwitchScene(EXIT_MENU);
}

void Application::Draw()
{
	ClearBackground(GRAY);

	if (shouldShowFilePicker)
	{
		if (GuiButton({ 200, 200, 250, 50 }, "Select Tile Map Json"))
		{
			const char* filterPatterns[] = { "*.json" };
			const char* file = tinyfd_openFileDialog("Open Json File", "", 1, filterPatterns, "Json Files", false);
			if (file) selectedJsonFile = file;
		}

		if (GuiButton({ 200, 250, 250, 50 }, "Select Tile Map PNG"))
		{
			const char* filterPatterns[] = { "*.png" };
			const char* file = tinyfd_openFileDialog("Open PNG File", "", 1, filterPatterns, "PNG Files", false);
			if (file) selectedPngFile = file;
			tileSet = LoadTexture(selectedPngFile.c_str());
		}

		if (GuiValueBox({ 200, 300, 125, 50 }, "Scale Value", &scaleValue, 1, 5, scaleEdit)) scaleEdit = !scaleEdit;

		if (GuiButton({ 325, 300, 125, 50 }, "Show TileMap"))
		{
			shouldShowFilePicker = false;
		}
		GuiLabel({ 200, 350, static_cast<float>(MeasureText(selectedJsonFile.c_str(), 20)), 20 }, selectedJsonFile.c_str());
		GuiLabel({ 200, 400, static_cast<float>(MeasureText(selectedPngFile.c_str(), 20)), 20 }, selectedPngFile.c_str());
	}
	else
	{
		DrawTilemap(selectedJsonFile.c_str(), tileSet, 16, scaleValue);
		std::string positionString = std::to_string(static_cast<int>(mousePosition.x)) + ", " + std::to_string(static_cast<int>(mousePosition.y));
		GuiLabel({ 0, 0, 100, 20 }, positionString.c_str());

		if (!colliders.empty())
		{
			for (auto& i : colliders)
				DrawRectangleLinesEx(i, 3, RED);
		}
	}

}

char* Application::ReadFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (!file) return NULL;

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(length + 1);
	fread(buffer, 1, length, file);
	buffer[length] = '\0'; // Null-terminate

	fclose(file);
	return buffer;
}

void Application::DrawTilemap(const char* jsonFile, Texture2D tileset, int tileSize, float scale) {
	char* jsonText = ReadFile(jsonFile);
	if (!jsonText) {
		printf("Failed to load JSON file\n");
		return;
	}

	cJSON* root = cJSON_Parse(jsonText);
	cJSON* layers = cJSON_GetObjectItem(root, "layers");  // Get all layers
	int width = cJSON_GetObjectItem(root, "width")->valueint;
	int height = cJSON_GetObjectItem(root, "height")->valueint;

	int tilesPerRow = tileset.width / tileSize;

	// Iterate through each layer
	cJSON* layer;
	cJSON_ArrayForEach(layer, layers) {
		cJSON* data = cJSON_GetObjectItem(layer, "data");  // Tile data for this layer
		if (!data) continue; // Skip non-tile layers (e.g., object layers)

		int i = 0;
		cJSON* tile;
		cJSON_ArrayForEach(tile, data) {
			int tileIndex = tile->valueint - 1; // Convert 1-based index to 0-based
			if (tileIndex >= 0) {
				int x = (i % width);
				int y = (i / width);

				Rectangle sourceRec = {
					(tileIndex % tilesPerRow) * tileSize,
					(tileIndex / tilesPerRow) * tileSize,
					tileSize, tileSize
				};

				// Scale position and size
				Rectangle destRec = {
					x * tileSize * scale,
					y * tileSize * scale,
					tileSize * scale,
					tileSize * scale
				};

				DrawTexturePro(tileset, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
			}
			i++;
		}
	}

	free(jsonText);
	cJSON_Delete(root);
}
#include "ExitMenu.h"

ExitMenu::ExitMenu(std::vector<Rectangle> colliders)
	: colliders(colliders), scrollOffset({ 0, 0 }), viewOffset({ 0, 0}), panelBounds({ 50, 50, 300, 200 }), contentBounds({ 0, 0, 500, 400 }), view({ 0, 0, panelBounds.width - 20, panelBounds.height - 20 })
{

}

void ExitMenu::Update()
{

}

void ExitMenu::Draw()
{
	GuiScrollPanel(panelBounds, "Test text", contentBounds, &scrollOffset, &view);
}

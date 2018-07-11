#include "Inventory.h"

#include "ResourceManager.h"

Inventory::Inventory()
	:
	background{ TextureManager::Get("Inventory\\Items Inventory") },
	opened{ false }
{
}

void Inventory::Draw(const Graphics& gfx)
{
	if (!opened) return;

	background.setPosition(gfx.MapPixelToCoords(sf::Vector2i{ 0, 0 }));
	gfx.Draw(background);
}

void Inventory::ToggleOpened()
{
	opened = !opened;
}
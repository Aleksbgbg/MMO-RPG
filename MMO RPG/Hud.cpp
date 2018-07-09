#include "Hud.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Hud::Draw(const Graphics& gfx) const
{
	for (int itemSlotIndex = 0; itemSlotIndex < ItemSlots; ++itemSlotIndex)
	{
		sf::RectangleShape rectangle{ sf::Vector2f{ static_cast<float>(ItemSlotDimension), static_cast<float>(ItemSlotDimension) } };

		rectangle.setOutlineColor(sf::Color{ 222, 222, 222 });
		rectangle.setOutlineThickness(2.0f);

		rectangle.setPosition(gfx.MapPixelToCoords(sf::Vector2i{ ItemSlotsHorizontalStart + ItemSlotDimension * itemSlotIndex, ItemSlotsVerticalPosition }));

		gfx.Draw(rectangle);
	}
}
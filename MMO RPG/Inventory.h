#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Graphics.h"

class Inventory
{
public:
	Inventory();

public:
	void Draw(const Graphics& gfx);

	void ToggleOpened();

private:
	sf::Sprite background;

	bool opened;
};
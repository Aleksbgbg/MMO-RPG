#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "Graphics.h"
#include "Inventory.h"

class Hud
{
public:
	void Draw(const Graphics& gfx);

	void KeyPressed(const sf::Keyboard::Key key);
	void MouseClicked(const sf::Vector2f position);

private:
	Inventory inventory;
};
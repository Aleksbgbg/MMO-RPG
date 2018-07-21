#pragma once

#include <SFML/Window/Keyboard.hpp>

#include "Graphics.h"
#include "Inventory.h"

class Hud
{
public:
	explicit Hud(Player& player);

public:
	void Draw(Graphics& gfx);

	void KeyPressed(const sf::Keyboard::Key key);
	void MouseClicked(const sf::Vector2f position);

private:
	sf::View view;

	std::vector<std::unique_ptr<HudWindow>> windows;
};
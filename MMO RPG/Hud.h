#pragma once

#include "Graphics.h"
#include "Inventory.h"

class Hud
{
public:
	explicit Hud(Player& player);

public:
	void Update();
	void Draw(Graphics& gfx);

private:
	sf::View view;

	std::vector<std::unique_ptr<HudWindow>> windows;
};
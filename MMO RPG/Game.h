#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics.h"
#include "Map.h"
#include "Player.h"
#include "Npc.h"

class Game
{
public:
	explicit Game(sf::RenderWindow& window);

	void Main();

private:
	void UpdateModel();
	void ComposeFrame();

private:
	Map map;

	Graphics gfx;

	Camera& camera;

	Player player;

	std::array<std::unique_ptr<Npc>, 8> npcs;
};
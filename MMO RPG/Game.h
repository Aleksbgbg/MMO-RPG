#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics.h"
#include "Map.h"
#include "Player.h"

class Game
{
public:
	explicit Game(sf::RenderWindow& window);

	void Main();

private:
	void UpdateModel();
	void ComposeFrame();

private:
	const Graphics _gfx;
	sf::RenderWindow& _window;
	Map map;
	Player _player;
};
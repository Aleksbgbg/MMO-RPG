#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics.h"
#include "Player.h"

class Game
{
public:
	Game(Game&) = delete;
	Game(Game&&) = delete;

	explicit Game(sf::RenderWindow& window);

	void Main();

private:
	void UpdateModel();
	void ComposeFrame();

private:
	Graphics _gfx;
	sf::RenderWindow& _window;

	Player _player;
};
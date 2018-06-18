#pragma once

#include <SFML/Graphics.hpp>

#include "Graphics.h"
<<<<<<< HEAD
#include "Map.h"
=======
#include "Player.h"
>>>>>>> upstream/master

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
<<<<<<< HEAD
	Map map;
=======

	Player _player;
>>>>>>> upstream/master
};
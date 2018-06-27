#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Graphics.h"
#include "World.h"

class Game
{
public:
	explicit Game(sf::RenderWindow& window);

	void Main();

private:
	void UpdateModel();
	void ComposeFrame();

private:
	Graphics gfx;

	Map map;

	Camera camera;

	World world;
};
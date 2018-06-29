#pragma once

#include <SFML/Graphics.hpp>

#include "Camera.h"
#include "Graphics.h"
#include "World.h"
#include "Minimap.h"

class Game
{
public:
	explicit Game(sf::RenderWindow& window);

	void Main();

private:
	void UpdateModel();
	void ComposeFrame();

	void ChangeActiveWorld(const int index);

private:
	static constexpr int Worlds = 2;

private:
	Graphics gfx;

	Camera camera;

	Player player;

	Map map;

	Minimap minimap;

	int currentActiveWorld;

	World* activeWorld;

	std::vector<World> worlds;
};
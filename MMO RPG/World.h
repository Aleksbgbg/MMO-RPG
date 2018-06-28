#pragma once

#include <array>

#include "Npc.h"
#include "Player.h"
#include "Minimap.h"

class World
{
public:
	World(std::string mapFile, Map& map, Player& player, Camera& camera, Minimap& minimap);

public:
	void Update();
	void Draw(const Graphics& gfx);

	void Activate();

private:
	sf::Vector2i dimensions;

	std::string mapFile;

	Map& map;

	Player& player;

	Camera& camera;

	Minimap& minimap;

	std::array<std::unique_ptr<Npc>, 8> npcs;
};
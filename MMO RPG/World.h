#pragma once

#include <array>

#include "Npc.h"
#include "Player.h"
#include "Minimap.h"

class World
{
public:
	World(Map& map, Player& player, Camera& camera, Minimap& minimap);

public:
	void Update();
	void Draw(const Graphics& gfx);

private:
	Map& map;

	Player& player;

	std::array<std::unique_ptr<Npc>, 8> npcs;
};

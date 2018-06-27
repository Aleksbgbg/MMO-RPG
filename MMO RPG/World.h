#pragma once

#include <array>

#include "Npc.h"
#include "Player.h"

class World
{
public:
	World(Map& map, Camera& camera);

public:
	void Update();
	void Draw(const Graphics& gfx);

private:
	Map& map;

	Camera& camera;

	Player player;

	std::array<std::unique_ptr<Npc>, 8> npcs;
};
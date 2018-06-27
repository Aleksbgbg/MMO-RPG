#include "World.h"

World::World(Map& map, Camera& camera)
	:
	map{ map },
	camera{ camera },
	player{ camera }
{
	constexpr int spritesheetWidth = 4;
	constexpr int spritesheetHeight = 2;

	for (int x = 0; x < spritesheetWidth; ++x)
	{
		for (int y = 0; y < spritesheetHeight; ++y)
		{
			npcs[x + y * spritesheetWidth] = std::make_unique<Npc>(sf::Vector2i{ x, y }, map);
		}
	}
}

void World::Update()
{
	player.Update();

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		npc->Update();
	}
}

void World::Draw(const Graphics& gfx)
{
	map.Draw(gfx);
	player.Draw(gfx);

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		npc->Draw(gfx);
	}
}
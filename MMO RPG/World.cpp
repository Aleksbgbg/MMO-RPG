#include "World.h"

World::World(Map& map, Player& player, Camera& camera, Minimap& minimap)
	:
	map{ map },
	player{ player }
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

	minimap.AddCharacter(player);

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		minimap.AddCharacter(*npc);
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
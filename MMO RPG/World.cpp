#include "World.h"

#include "json.hpp"

#include <fstream>

using json = nlohmann::json;

World::World(const std::string& mapFile, Map& map, Player& player, Camera& camera, Minimap& minimap)
	:
	mapFile{ mapFile },
	map{ map },
	player{ player },
	camera{ camera },
	minimap{ minimap }
{
	{
		std::ifstream mapFileStream{ mapFile };

		if (!mapFileStream.is_open())
		{
			throw std::runtime_error{ "Could not open map file." };
		}

		json mapData = json::parse(mapFileStream);

		const sf::Vector2i mapDimensions{ mapData["width"], mapData["height"] };
		const sf::Vector2i tileDimensions{ mapData["tilewidth"], mapData["tileheight"] };

		dimensions = sf::Vector2i{ static_cast<int>(mapDimensions.x * tileDimensions.x * Map::Scale), static_cast<int>(mapDimensions.y * tileDimensions.y * Map::Scale) };
	}

	constexpr int spritesheetWidth = 4;
	constexpr int spritesheetHeight = 2;

	for (int x = 0; x < spritesheetWidth; ++x)
	{
		for (int y = 0; y < spritesheetHeight; ++y)
		{
			npcs[x + y * spritesheetWidth] = std::make_unique<Npc>(sf::Vector2i{ x, y }, dimensions);
		}
	}
}
void World::Update()
{
	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		npc->Update();
	}
}

void World::Draw(const Graphics& gfx)
{
	map.Draw(gfx);

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		npc->Draw(gfx);
	}
}

void World::Activate()
{
	map.Load(mapFile);

	camera.ReCalibrate();
	minimap.LoadNewWorld(sf::Vector2f{ map.GetDimensions() });

	minimap.AddCharacter(player);

	for (const std::unique_ptr<Npc>& npc : npcs)
	{
		minimap.AddCharacter(*npc);
	}
}
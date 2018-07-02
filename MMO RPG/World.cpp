#include "World.h"

#include "json.hpp"

#include "Collider.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "Json.h"

using nlohmann::json;

World::World(const std::string& mapFile, Map& map, Player& player, Minimap& minimap, json& worldConfig)
	:
	mapFile{ mapFile },
	map{ map },
	player{ player },
	minimap{ minimap }
{
	{
		const json mapData = read_json("Maps\\" + mapFile);

		const sf::Vector2i mapDimensions{ mapData["width"], mapData["height"] };
		const sf::Vector2i tileDimensions{ mapData["tilewidth"], mapData["tileheight"] };

		dimensions = sf::Vector2i{ static_cast<int>(mapDimensions.x * tileDimensions.x * Map::Scale), static_cast<int>(mapDimensions.y * tileDimensions.y * Map::Scale) };

		for (const json& portal : worldConfig["portals"])
		{
			portals.emplace_back(sf::FloatRect{ static_cast<int>(portal["x"]) * tileDimensions.x * Map::Scale, static_cast<int>(portal["y"]) * tileDimensions.y * Map::Scale, tileDimensions.x * Map::Scale * 2, tileDimensions.y * Map::Scale * 2 }, portal["targetWorldIndex"], portal["targetPortalIndex"]);
		}
	}

	if (worldConfig["type"] == "NPC")
	{
		const json npcConfigFile = read_json("Config\\NPC.json");

		constexpr int spritesheetWidth = 4;
		constexpr int spritesheetHeight = 2;

		for (int x = 0; x < spritesheetWidth; ++x)
		{
			for (int y = 0; y < spritesheetHeight; ++y)
			{
				characters.emplace_back(std::make_unique<Npc>(sf::Vector2i{ x, y }, dimensions, npcConfigFile));
			}
		}
	}
	else if (worldConfig["type"] == "PVE")
	{
		for (const json& enemy : worldConfig["enemies"])
		{
			const std::string& type = enemy["type"];

			const sf::Texture& texture = TextureManager::Get(type);

			const int enemyCount = enemy["quantity"];

			const json configFile = read_json("Config\\" + type + ".json");

			for (int iteration = 0; iteration < enemyCount; ++iteration)
			{
				characters.emplace_back(std::make_unique<Enemy>(texture, dimensions, configFile));
			}
		}
	}
}

void World::Update()
{
	for (const std::unique_ptr<Character>& character : characters)
	{
		character->Update();
	}
}

void World::Draw(Graphics& gfx)
{
	for (const std::unique_ptr<Character>& character : characters)
	{
		character->Draw(gfx);
	}

	minimap.Render(gfx, player, characters);
}

void World::Activate() const
{
	map.Load(mapFile);

	minimap.LoadNewWorld(sf::Vector2f{ map.GetDimensions() });
}

bool World::PlayerCanTeleport() const
{
	return std::any_of(portals.begin(), portals.end(), [this](const Portal& portal)
	{
		return is_inside(portal.occupation, player.GetOccupation());
	});
}

const Portal& World::GetPortal(const int index) const
{
	return portals[index];
}

const Portal& World::FindNearestPortal() const
{
	for (const Portal& portal : portals)
	{
		if (is_inside(portal.occupation, player.GetOccupation()))
		{
			return portal;
		}
	}

	throw std::runtime_error{ "No near portal exists." };
}
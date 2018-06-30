#include <SFML/Graphics.hpp>

#include "json.hpp"

#include <fstream>

#include "Graphics.h"
#include "Map.h"
#include "TextureManager.h"

using json = nlohmann::json;

void Map::Draw(const Graphics& gfx)
{
	for (const Tile& tile : tiles)
	{
		tile.Draw(gfx);
	}
}

void Map::Load(const std::string& filename)
{
	tiles.clear();

	json mapDetails;

	{
		std::ifstream input{ "Maps\\" + filename };

		if (!input.is_open())
		{
			throw std::runtime_error{ "Could not open file " + filename };
		}

		mapDetails = json::parse(input);
	}

	mapTiles = sf::Vector2i{ mapDetails["width"], mapDetails["height"] };

	tileDimensions = sf::Vector2i{ mapDetails["tilewidth"], mapDetails["tileheight"] };

	const sf::Texture& mapTexture = TextureManager::Get("Map");

	const sf::Vector2i tileCount{ static_cast<int>(mapTexture.getSize().x) / tileDimensions.x, static_cast<int>(mapTexture.getSize().y) / tileDimensions.y };

	for (const json& layer : mapDetails["layers"])
	{
		const json& layerData = layer["data"];

		int index = -1;

		for (int y = 0; y < mapTiles.y; ++y)
		{
			for (int x = 0; x < mapTiles.x; ++x)
			{
				int tileIndex = layerData[++index];

				if (tileIndex > 0)
				{
					tileIndex -= 1;

					const int tileColumn = tileIndex % tileCount.x;
					const int tileRow = tileIndex / tileCount.x;

					tiles.emplace_back(mapTexture, sf::Vector2i{ tileColumn * tileDimensions.x, tileRow * tileDimensions.y }, sf::Vector2f{ static_cast<float>(x * tileDimensions.x), static_cast<float>(y * tileDimensions.y) }, Scale, tileDimensions);
				}
			}
		}
	}
}

sf::Vector2i Map::GetDimensions() const
{
	return sf::Vector2i{ static_cast<int>(mapTiles.x * tileDimensions.x * Scale), static_cast<int>(mapTiles.y * tileDimensions.y * Scale) };
}
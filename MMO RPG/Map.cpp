#include <SFML/Graphics.hpp>

#include "json.hpp"

#include <fstream>
#include <string>

#include "Graphics.h"
#include "Map.h"
#include "TextureManager.h"

using json = nlohmann::json;

Map::Map()
	:
	texture{ TextureManager::Get("mapTest") }
{
	// TODO: Remove hardcoded
	ParseFileToJson("mapTest.json");
	PopulateSpritePositions();
}

void Map::AddTexture(const sf::Texture& texture)
{
	textures.push_back(texture);
}

void Map::Draw(const Graphics& gfx)
{
	for (const sf::Sprite& sprite : sprites)
	{
		gfx.Draw(sprite);
	}
}

void Map::AddSprite(const int index, const int width, const int height)
{
	sf::Sprite sprite{ };

	sprite.setTexture(textures.front());
	sprite.setTextureRect(sf::IntRect{ spritePositions[index].x, spritePositions[index].y, width, height });
	sprite.setScale(2.0f, 2.0f);
	sprite.setPosition(0, 0);

	sprites.push_back(sprite);
}

void Map::ParseFileToJson(const std::string& filename)
{
	std::ifstream input{ filename };

	if (!input.is_open())
	{
		throw std::runtime_error{ "Could not open file " + filename };
	}

	json = json::parse(input);
}

void Map::PopulateSpritePositions()
{
	// TODO: Maybe move this into it's own method
	const int tilesHorizontal = texture.getSize().x / 16;
	const int tilesVertical = texture.getSize().y / 16;
	const int tilesTotal = tilesHorizontal * tilesVertical;

	unsigned int xPos = 0;
	unsigned int yPos = 0;

	for (int i = 0; i < tilesTotal; i++)
	{
		spritePositions.emplace_back(xPos, yPos);

		xPos += 16;

		// TODO: Remove hardcoded number
		if (xPos == texture.getSize().x)
		{
			xPos = 0;
			yPos += 16;
		}
	}
}

void Map::UnpackData()
{
	width = json["width"];
	height = json["height"];
	layers = json["layers"].size();
}
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
	AddAllSprites();
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

void Map::AddSprite(const int index, const float x, const float y, const int width, const int height)
{
	sf::Sprite sprite{ };

	sprite.setTexture(TextureManager::Get("mapTest"));
	sprite.setTextureRect(sf::IntRect{ spritePositions[index].x, spritePositions[index].y, width, height });
	sprite.setScale(2.0f, 2.0f);
	sprite.setPosition(x, y);

	sprites.push_back(sprite);
}

nlohmann::json Map::GetJsonData() const
{
	return jsonData;
}

nlohmann::json Map::GetAllLayers() const
{
	return jsonData["layers"];
}

nlohmann::json Map::GetLayerData(int layerId) const
{
	return GetAllLayers()["layers"]["data"];
}

sf::Vector2i Map::GetDimensions() const
{
	return sf::Vector2i(GetTileAmount().x * GetTileSize().x, GetTileAmount().y * GetTileSize().y);
}

sf::Vector2i Map::GetTileAmount() const
{
	return sf::Vector2i(jsonData["width"], jsonData["height"]);
}

sf::Vector2i Map::GetTileSize() const
{
	/*
	// So we can apply scaling meme
	// TODO: Rename?!?
	const int actualWidth = static_cast<int>(jsonData["tilewidth"]) * sprites.back().getScale().x;
	const int actualHeight = static_cast<int>(jsonData["tileheight"]) * sprites.back().getScale().y;
	*/
	const int actualHeight = static_cast<int>(jsonData["tileheight"]) * sprites.back().getScale().y;


	// TODO: Sort out loading order issue and remove hard coded value
	return sf::Vector2i(static_cast<int>(jsonData["tilewidth"]) * 2, static_cast<int>(jsonData["tileheight"])* 2);
}

void Map::AddAllSprites()
{
	int screenWidth = Graphics::ScreenWidth;
	int screenHeight = Graphics::ScreenWidth;

	// This is post scaling so don't multiply it or do any other magic spells
	// TODO: Probably change this from direct access
	const json tileWidth = jsonData["tilewidth"];
	const json tileHeight = jsonData["tileheight"];

	const json layers = GetAllLayers();
	const int totalWidth = GetTileAmount().x;

	// TODO: Probably change this from direct access
	for (json layer : layers)
	{
		json data = layer["data"];
		
		int tileX = 0, tileY = 0;

		for (int tileId : data)
		{
			// Gotta -1 because the JSON data reserves 0 for no sprite and as such minusing one gets us back on track because our Vector stores from 0
			// TODO: Maybe make the this clearer somehow
			if(tileId > 0)
			{
				tileId -= 1;
				// This must be unscaled... this is maybe a crap thing
				AddSprite(tileId, tileX, tileY, tileWidth, tileHeight);
			}

			// TODO: Look into why tileWidth above is wrong
			// SOLUTION: Was scaling elsewhere
			tileX += 32;
			
			// TODO: Make sure hardcdoded val is changed along with other TOOD's
			if (tileX == GetDimensions().x)
			{
				tileX = 0;
				// TODO: Look into why tileHeight above is wrong
				// SOLUTION: Was scaling elsewhere
				tileY += 32;
			}
		}
	}
}

void Map::ParseFileToJson(const std::string& filename)
{
	std::ifstream input{ filename };

	if (!input.is_open())
	{
		throw std::runtime_error{ "Could not open file " + filename };
	}

	jsonData = json::parse(input);
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

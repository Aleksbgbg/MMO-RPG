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

void Map::AddSprite(const int index, const float x, const float y, const int width, const int height)
{
	sf::Sprite sprite{ };

	sprite.setTexture(textures.front());
	sprite.setTextureRect(sf::IntRect{ spritePositions[index].x, spritePositions[index].y, width, height });
	sprite.setScale(2.0f, 2.0f);
	sprite.setPosition(x, y);

	sprites.push_back(sprite);
}

void Map::AddAllSprites(const Graphics& gfx)
{
	int screenWidth = gfx.ScreenWidth;
	int screenHeight = gfx.ScreenWidth;

	json tileWidth = jsonData["tilewidth"];
	json tileHeight = jsonData["tileheight"];
	json layers = jsonData["layers"];
	int totalWidth = jsonData["width"];

	for (json layer : layers)
	{
		// TODO: Maybe do some renaming
		// Re-implement the Unpack function so we can keep this function tidy
		json data = layer["data"];
		int height = layer["height"];
		std::string name = layer["name"];
		int opacity = layer["opacity"];
		std::string type = layer["type"];
		bool visible = layer["visible"];
		int width = layer["width"];
		int x = layer["x"];
		int y = layer["y"];
		
		float tileX = 0, tileY = 0;

		for (int tileID : data)
		{
			AddSprite(tileID, tileX, tileY, tileWidth, tileHeight);

			// TODO: Look into why tileWidth above is wrong
			tileX += 32;
			
			// TODO: Make sure hardcdoded val is changed along with other TOOD's
			if (tileX == totalWidth * 32)
			{
				tileX = 0;
				// TODO: Look into why tileHeight above is wrong
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

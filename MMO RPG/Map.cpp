#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Map.h"

#include "../Libraries/json.hpp"

using json = nlohmann::json;

Map::Map()
{
	// TODO: Remove hardcoded
	texture.loadFromFile("mapTest.png");
	ParseFileToJSON("mapTest.json");
	PopulateSpritePositions();
}

void Map::AddTexture(sf::Texture texture)
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

void Map::AddSprite(int index, int w, int h)

{
	// Hey so I heard you like memory
	spr.setTexture(textures.front());
	spr.setTextureRect(sf::IntRect(spritePositions[index].x, spritePositions[index].y, w, h));
	spr.setScale(2.0f, 2.0f);
	spr.setPosition(0, 0);
	sprites.push_back(spr);
}

void Map::ParseFileToJSON(std::string fileName)
{
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Could not open file " + fileName);
	}
	json = json::parse(input);
}

void Map::PopulateSpritePositions()
{
	// TODO: Maybe move this into it's own method
	int numOfTilesX = texture.getSize().x / 16;
	int numOfTilesY = texture.getSize().y / 16;
	int numOfAllTiles = numOfTilesX * numOfTilesY;

	unsigned int xPos = 0;
	unsigned int yPos = 0;

	for (int i = 0; i != numOfAllTiles; i++)
	{
		spritePositions.push_back(sf::Vector2i(xPos, yPos));

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

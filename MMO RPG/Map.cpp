#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Map.h"

#include "../Libraries/json.hpp"

using json = nlohmann::json;

Map::Map(Graphics& gfx)
	:
	_gfx{ gfx }
{
	// TODO: Remove hardcoded
	_texture.loadFromFile("mapTest.png");
	ParseFileToJSON("mapTest.json");
	PopulateSpritePositions();
}

void Map::AddTexture(sf::Texture texture)
{
	_textures.push_back(texture);
}

void Map::AddSprite(int index, int w, int h)

{
	// Hey so I heard you like memory
	spr.setTexture(_textures.front());
	spr.setTextureRect(sf::IntRect(_spritePositions[index].x, _spritePositions[index].y, w, h));
	spr.setScale(2.0f, 2.0f);
	spr.setPosition(0, 0);
	_sprites.push_back(spr);

	_gfx.Add(_sprites.back());
}

void Map::ParseFileToJSON(std::string fileName)
{
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		throw std::runtime_error("Could not open file " + fileName);
	}
	_json = json::parse(input);
}

void Map::PopulateSpritePositions()
{
	// TODO: Maybe move this into it's own method
	int numOfTilesX = _texture.getSize().x / 16;
	int numOfTilesY = _texture.getSize().y / 16;
	int numOfAllTiles = numOfTilesX * numOfTilesY;

	unsigned int xPos = 0;
	unsigned int yPos = 0;

	for (int i = 0; i != numOfAllTiles; i++)
	{
		_spritePositions.push_back(sf::Vector2i(xPos, yPos));

		xPos += 16;

		// TODO: Remove hardcoded number
		if (xPos == _texture.getSize().x)
		{
			xPos = 0;
			yPos += 16;
		}
	}
}

void Map::UnpackData()
{
	_width = _json["width"];
	_height = _json["height"];
	_layers = _json["layers"].size();
}

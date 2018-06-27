#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tile.h"

class Graphics;

class Map
{
public:
	Map();

public:
	void Draw(const Graphics& gfx);

public:
	static constexpr float Scale = 2.0f;

public:
	sf::Vector2i GetDimensions() const;

private:
	sf::Vector2i mapTiles;
	sf::Vector2i tileDimensions;

	std::vector<Tile> tiles;
};
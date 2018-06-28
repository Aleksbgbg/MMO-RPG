#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Tile.h"

class Map
{
public:
	void Draw(const Graphics& gfx);

	void Load(const std::string& filename);

public:
	sf::Vector2i GetDimensions() const;

public:
	static constexpr float Scale = 2.0f;

private:
	sf::Vector2i mapTiles;
	sf::Vector2i tileDimensions;

	std::vector<Tile> tiles;
};
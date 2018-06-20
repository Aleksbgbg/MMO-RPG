#pragma once

#include <SFML/Graphics.hpp>

#include "json.hpp"

#include <string>
#include <vector>

class Map
{
public:
	Map();

public:
	void AddTexture(const sf::Texture& texture);
	void AddAllSprites(const Graphics& gfx);
	void Draw(const Graphics& gfx);
	void AddSprite(const int index, const float x, const float y, const int width, const int height);

private:
	void PopulateSpritePositions();
	void ParseFileToJson(const std::string& filename);
	void UnpackData();



private:
	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;

	nlohmann::json jsonData;

	int width;
	int height;
	int layers;

	const sf::Texture& texture;
	std::vector<sf::Vector2i> spritePositions;
};
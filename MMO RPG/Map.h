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
	void AddSprite(int index, int width, int height);
	void AddTexture(const sf::Texture& texture);
	
	void Draw(const Graphics& gfx);

private:
	void PopulateSpritePositions();
	void ParseFileToJson(const std::string& filename);
	void UnpackData();

private:
	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;

	nlohmann::json json;

	int width;
	int height;
	int layers;

	const sf::Texture& texture;
	std::vector<sf::Vector2i> spritePositions;
};
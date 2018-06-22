#pragma once

#include <SFML/Graphics.hpp>

#include "json.hpp"

#include <string>
#include <vector>


class Graphics;

class Map
{
public:
	Map();

public:
	void AddTexture(const sf::Texture& texture);
	void AddAllSprites();
	void Draw(const Graphics& gfx);
	void AddSprite(const int index, const float x, const float y, const int width, const int height);

public:
	nlohmann::json GetJsonData() const;
	nlohmann::json GetAllLayers() const;
	nlohmann::json GetLayerData(int layerId) const;

	sf::Vector2i GetDimensions() const;
	sf::Vector2i GetTileAmount() const;
	sf::Vector2i GetTileSize() const;


private:
	void PopulateSpritePositions();
	void ParseFileToJson(const std::string& filename);



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
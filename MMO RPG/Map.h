#pragma once
#include <string>
#include "../Libraries/json.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
using json = nlohmann::json;

class Map
{
public:
	Map();
	void AddSprite(int index, int w, int h);
	void AddTexture(sf::Texture texture);
	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;
	sf::Sprite* sprite;

	sf::Sprite spr;

	void Draw(const Graphics& gfx);


private:
	json json;
	int width;
	int height;
	int layers;
	sf::Texture texture;
	std::vector<sf::Vector2i> spritePositions;
	void PopulateSpritePositions();
	void ParseFileToJSON(std::string fileName);
	void UnpackData();
};
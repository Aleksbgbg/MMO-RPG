#pragma once
#include <string>
#include "../Libraries/json.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Graphics.h"
using json = nlohmann::json;

class Map
{
public:
	Map(Graphics& gfx);
	void AddSprite(int index, int w, int h);
	void AddTexture(sf::Texture texture);
	std::vector<sf::Texture> _textures;
	std::vector<sf::Sprite> _sprites;
	sf::Sprite* sprite;

	sf::Sprite spr;


private:
	json _json;
	int _width;
	int _height;
	int _layers;
	sf::Texture _texture;
	std::vector<sf::Vector2i> _spritePositions;
	void PopulateSpritePositions();
	void ParseFileToJSON(std::string fileName);
	void UnpackData();

	Graphics& _gfx;
};
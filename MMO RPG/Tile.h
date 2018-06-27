#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Graphics;

class Tile
{
public:
	Tile(const sf::Texture& mapTexture, const sf::Vector2i texturePosition, const sf::Vector2f mapPosition, const float scale, const sf::Vector2i tileSize);

public:
	void Draw(const Graphics& gfx) const;

private:
	sf::Sprite sprite;
};
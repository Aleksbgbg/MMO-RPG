#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Sprite.h"

class Graphics;

class Tile
{
public:
	Tile(const std::shared_ptr<sf::Texture>& mapTexture, const sf::Vector2i texturePosition, const sf::Vector2f mapPosition, const float scale, const sf::Vector2i tileSize);

public:
	void Draw(const Graphics& gfx) const;

private:
	Sprite sprite;
};
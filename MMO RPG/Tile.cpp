#include "Tile.h"

#include "Graphics.h"

Tile::Tile(const std::shared_ptr<sf::Texture>& mapTexture, const sf::Vector2i texturePosition, const sf::Vector2f mapPosition, const float scale, const sf::Vector2i tileSize)
	:
	sprite{ mapTexture, sf::IntRect{ texturePosition.x, texturePosition.y, tileSize.x, tileSize.y } }
{
	sprite.scale(scale, scale);
	sprite.setPosition(mapPosition * scale);
}

void Tile::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}
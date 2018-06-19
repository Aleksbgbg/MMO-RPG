#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>

struct SpriteInfo
{
	SpriteInfo(const std::string& filename, const sf::Texture& spriteSheet);

	sf::Vector2u spriteDimension;
	sf::Vector2u frameRegion;
	sf::Vector2u sheetSize;

	int leftRow;
	int rightRow;
	int upRow;
	int downRow;

	int standingFrameIndex;
	int frameCount;

	float frameTime;
};
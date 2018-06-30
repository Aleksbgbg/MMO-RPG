#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <json.hpp>

struct SpriteInfo
{
	SpriteInfo(const nlohmann::json& config, const sf::Texture& spriteSheet);

	sf::Vector2u spriteDimension;
	sf::Vector2u frameRegion;
	sf::Vector2u sheetSize;

	static constexpr unsigned int RowCount = 4;

	int leftRow;
	int rightRow;
	int upRow;
	int downRow;

	int standingFrameIndex;
	int frameCount;

	float frameTime;
};
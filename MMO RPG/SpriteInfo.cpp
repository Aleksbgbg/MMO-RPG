#include "SpriteInfo.h"

#include <INIReader.h>

SpriteInfo::SpriteInfo(const std::string& filename, const sf::Texture& spriteSheet)
	:
	sheetSize{ spriteSheet.getSize() }
{
	INIReader iniReader{ filename };

	frameTime = iniReader.GetReal("Sprite", "AnimationTime", 0);

	spriteDimension = sf::Vector2u{ static_cast<unsigned int>(iniReader.GetInteger("Sprite", "Width", 0)), static_cast<unsigned int>(iniReader.GetInteger("Sprite", "Height", 0)) };

	standingFrameIndex = iniReader.GetInteger("SpriteSheet", "StandingFrameIndex", 0);

	leftRow = iniReader.GetInteger("SpriteSheet", "LeftRow", 0);
	rightRow = iniReader.GetInteger("SpriteSheet", "RightRow", 0);
	upRow = iniReader.GetInteger("SpriteSheet", "UpRow", 0);
	downRow = iniReader.GetInteger("SpriteSheet", "DownRow", 0);

	frameCount = sheetSize.x / spriteDimension.x;

	frameRegion = sf::Vector2u{ sheetSize.x, spriteDimension.y };
}
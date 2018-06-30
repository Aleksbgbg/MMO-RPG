#include "SpriteInfo.h"

using json = nlohmann::json;

SpriteInfo::SpriteInfo(const json& config, const sf::Texture& spriteSheet)
	:
	sheetSize{ spriteSheet.getSize() }
{
	const json& spriteConfig = config["sprite"];
	const json& spriteSheetConfig = config["spriteSheet"];

	frameTime = spriteConfig["animationTime"];

	spriteDimension = sf::Vector2u{ spriteConfig["width"], spriteConfig["height"] };

	standingFrameIndex = spriteSheetConfig["standingFrameIndex"];

	leftRow = spriteSheetConfig["leftRow"];
	rightRow = spriteSheetConfig["rightRow"];
	upRow = spriteSheetConfig["upRow"];
	downRow = spriteSheetConfig["downRow"];

	frameCount = spriteSheetConfig["walkingFrames"];

	frameRegion = sf::Vector2u{ spriteDimension.x * frameCount, spriteDimension.y };
}
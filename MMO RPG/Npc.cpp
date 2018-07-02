#include "Npc.h"

#include "Random.h"
#include "ResourceManager.h"
#include "Map.h"

using nlohmann::json;

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Npc{ spriteSheetCoordinate, TextureManager::Get("NPCs"), mapDimensions, spriteConfig }
{
}

Npc::Npc(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Character{ sf::Sprite{ spriteSheet }, movementStrategy },
	spriteInfo{ spriteConfig, spriteSheet },
	movementStrategy{ sprite, Random::GenerateFloat(1.0f, 2.0f), mapDimensions }
{
	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ sf::Vector2i{ 0, 0 }, spriteSheetDimension };

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Character{ sf::Sprite{ spriteSheet }, movementStrategy },
	spriteInfo{ spriteConfig, spriteSheet },
	movementStrategy{ sprite, Random::GenerateFloat(1.0f, 2.0f), mapDimensions }
{
	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ spriteSheetCoordinate.x * spriteSheetDimension.x, spriteSheetCoordinate.y * spriteSheetDimension.y, spriteSheetDimension.x, spriteSheetDimension.y };

	//sprite.setPosition(static_cast<float>(Random::Generate(0, mapDimensions.x - spriteInfo.spriteDimension.x)), static_cast<float>(Random::Generate(0, mapDimensions.y - spriteInfo.spriteDimension.y)));

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}
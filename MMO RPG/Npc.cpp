#include "Npc.h"

#include "Random.h"
#include "ResourceManager.h"
#include "Map.h"

using json = nlohmann::json;

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Npc{ spriteSheetCoordinate, TextureManager::Get("NPCs"), mapDimensions, spriteConfig }
{
}

Npc::Npc(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Character{ sf::Sprite{ spriteSheet }, Random::GenerateFloat(1.0f, 2.0f) },
	mapDimensions{ mapDimensions },
	spriteInfo{ spriteConfig, spriteSheet }
{
	GenerateTargetPosition();

	sprite.setPosition(targetPosition);

	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ sf::Vector2i{ 0, 0 }, spriteSheetDimension };

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Character{ sf::Sprite{ spriteSheet }, Random::GenerateFloat(1.0f, 2.0f) },
	mapDimensions{ mapDimensions },
	spriteInfo{ spriteConfig, spriteSheet }
{
	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ spriteSheetCoordinate.x * spriteSheetDimension.x, spriteSheetCoordinate.y * spriteSheetDimension.y, spriteSheetDimension.x, spriteSheetDimension.y };

	GenerateTargetPosition();

	sprite.setPosition(targetPosition);

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

sf::Vector2f Npc::PickMovement()
{
	const sf::Vector2f currentPosition{ sprite.getPosition() };

	sf::Vector2f movement;

	if (currentPosition.x != targetPosition.x) // Move towards target x first
	{
		if (currentPosition.x > targetPosition.x)
		{
			movement.x = -1;
		}
		else
		{
			movement.x = 1;
		}
	}
	else // Move towards target y, after reaching target x
	{
		if (currentPosition.y > targetPosition.y)
		{
			movement.y = -1;
		}
		else
		{
			movement.y = 1;
		}
	}

	return movement;
}

void Npc::OnPositionUpdated(const sf::Vector2f newPosition)
{
	if (newPosition == targetPosition)
	{
		GenerateTargetPosition();
		return;
	}

	const sf::Vector2f currentVector = newPosition - targetPosition;

	if (!(currentVector.x == 0 || (startingTargetVector.x >= 0 ^ currentVector.x < 0)))
	{
		SetPosition(sf::Vector2f{ targetPosition.x, sprite.getPosition().y });
	}

	if (!(currentVector.y == 0 || (startingTargetVector.y >= 0 ^ currentVector.y < 0)))
	{
		SetPosition(sf::Vector2f{ sprite.getPosition().x, targetPosition.y });
	}
}

void Npc::GenerateTargetPosition()
{
	// Consider checking if the NPC is set a target position already equal to the current position, and choose a new target if so (may not be necessary)

	targetPosition.x = static_cast<float>(Random::Generate(0, mapDimensions.x - spriteInfo.spriteDimension.x));
	targetPosition.y = static_cast<float>(Random::Generate(0, mapDimensions.y - spriteInfo.spriteDimension.y));

	startingTargetVector = sprite.getPosition() - targetPosition;
}
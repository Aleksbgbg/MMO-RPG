#include "Npc.h"

#include "Random.h"
#include "TextureManager.h"

Npc::Npc(const sf::Vector2i spriteSheetCoordinate)
	:
	Npc{ spriteSheetCoordinate, TextureManager::Get("NPCs") }
{
}

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet)
	:
	Character{ sf::Sprite{ spriteSheet }, Random::GenerateFloat(1.0f, 3.0f) },
	spriteInfo{ "Npc Sprite Config.ini", spriteSheet }
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
			movementDirection = Direction::Left;
			movement.x = -1;
		}
		else
		{
			movementDirection = Direction::Right;
			movement.x = 1;
		}
	}
	else // Move towards target y, after reaching target x
	{
		if (currentPosition.y > targetPosition.y)
		{
			movementDirection = Direction::Up;
			movement.y = -1;
		}
		else
		{
			movementDirection = Direction::Down;
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

	if (!(currentVector.x == 0 || startingTargetVector.x >= 0 ^ currentVector.x < 0))
	{
		SetPosition(sf::Vector2f{ targetPosition.x, sprite.getPosition().y });
	}
	
	if (!(currentVector.y == 0 || startingTargetVector.y >= 0 ^ currentVector.y < 0))
	{
		SetPosition(sf::Vector2f{ sprite.getPosition().x, targetPosition.y });
	}
}

void Npc::GenerateTargetPosition()
{
	targetPosition.x = static_cast<float>(Random::Generate(0, Graphics::ScreenWidth - spriteInfo.spriteDimension.x));
	targetPosition.y = static_cast<float>(Random::Generate(0, Graphics::ScreenHeight - spriteInfo.spriteDimension.y));

	startingTargetVector = sprite.getPosition() - targetPosition;
}
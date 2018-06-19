#include "Npc.h"

#include "Random.h"

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, sf::Texture& spriteSheet)
	:
	Character{ sf::Sprite{ spriteSheet, } },
	spriteInfo{ "Npc Sprite Config.ini", spriteSheet }
{
	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ spriteSheetCoordinate.x * spriteSheetDimension.x, spriteSheetCoordinate.y * spriteSheetDimension.y, spriteSheetDimension.x, spriteSheetDimension.y };

	GenerateTargetPosition();

	sprite.setPosition(sf::Vector2f{ targetPosition });

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

sf::Vector2f Npc::PickMovement()
{
	const sf::Vector2i currentPosition{ sprite.getPosition() };

	if (currentPosition == targetPosition)
	{
		GenerateTargetPosition();
	}

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

void Npc::GenerateTargetPosition()
{
	targetPosition.x = Random::Generate(0, Graphics::ScreenWidth - spriteInfo.spriteDimension.x);
	targetPosition.y = Random::Generate(0, Graphics::ScreenHeight - spriteInfo.spriteDimension.y);
}
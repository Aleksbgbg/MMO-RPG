#include "SimpleAiMovement.h"

#include "Random.h"

SimpleAiMovement::SimpleAiMovement(sf::Sprite& sprite, const float speed, const sf::Vector2i mapDimensions)
	:
	MovementStrategy{ sprite, speed },
	mapDimensions{ mapDimensions },
	spriteDimensions{ sprite.getLocalBounds().width, sprite.getLocalBounds().height }
{
	const sf::Vector2f randomPosition = GenerateRandomPosition();

	targetPosition = randomPosition;
	ForcePosition(randomPosition);
}

sf::Vector2f SimpleAiMovement::PickMovement(const sf::Vector2f position)
{
	// Force backtracking if overshot target
	{
		const sf::Vector2f currentVector = position - targetPosition;

		if (!(currentVector.x == 0 || (initialTargetVector.x >= 0 ^ currentVector.x < 0)))
		{
			ForcePosition(sf::Vector2f{ targetPosition.x, position.y });
		}

		if (!(currentVector.y == 0 || (initialTargetVector.y >= 0 ^ currentVector.y < 0)))
		{
			ForcePosition(sf::Vector2f{ position.x, targetPosition.y });
		}
	}

	if (position == targetPosition)
	{
		GenerateTargetPosition(position);
	}

	sf::Vector2f movement;

	if (position.x != targetPosition.x) // Move towards target x first
	{
		if (position.x > targetPosition.x)
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
		if (position.y > targetPosition.y)
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

void SimpleAiMovement::GenerateTargetPosition(const sf::Vector2f position)
{
	do
	{
		targetPosition = GenerateRandomPosition();
	} while (position == targetPosition);

	initialTargetVector = position - targetPosition;
}

sf::Vector2f SimpleAiMovement::GenerateRandomPosition() const
{
	return sf::Vector2f{ static_cast<float>(Random::Generate(0, mapDimensions.x - spriteDimensions.x)), static_cast<float>(Random::Generate(0, mapDimensions.y - spriteDimensions.y)) };
}
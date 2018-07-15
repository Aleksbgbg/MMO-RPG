#pragma once

#include "MovementStrategy.h"

class SimpleAiMovement : public MovementStrategy
{
public:
	SimpleAiMovement(Sprite& sprite, const float speed, const sf::Vector2i mapDimensions);

protected:
	sf::Vector2f PickMovement(sf::Vector2f position) override;

private:
	void GenerateTargetPosition(const sf::Vector2f position);
	sf::Vector2f GenerateRandomPosition() const;

private:
	const sf::Vector2i mapDimensions;
	const sf::Vector2f spriteDimensions;

	sf::Vector2f targetPosition;

	sf::Vector2f initialTargetVector;
};
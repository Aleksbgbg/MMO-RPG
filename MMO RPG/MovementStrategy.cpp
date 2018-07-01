#include "MovementStrategy.h"
#include "Vector.h"

MovementStrategy::MovementStrategy(sf::Sprite& sprite, const float speed)
	:
	sprite{ sprite },
	speed{ speed }
{
}

void MovementStrategy::ForcePosition(const sf::Vector2f position) const
{
	sprite.setPosition(position);
}

sf::Vector2f MovementStrategy::Move()
{
	sf::Vector2f movement = PickMovement(sprite.getPosition());

	normalize(movement);

	movement *= speed;

	sprite.move(movement);

	return movement;
}
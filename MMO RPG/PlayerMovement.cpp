#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(sf::Sprite& sprite, const float speed, const std::unordered_map<Direction, std::vector<sf::Keyboard::Key>>& directionKeys)
	:
	MovementStrategy{ sprite, speed },
	directionKeys{ directionKeys }
{
}

sf::Vector2f PlayerMovement::PickMovement(const sf::Vector2f position)
{
	sf::Vector2f movement;

	if (std::any_of(directionKeys.at(Direction::Up).begin(), directionKeys.at(Direction::Up).end(), sf::Keyboard::isKeyPressed))
	{
		movement.y -= 1;
	}
	
	if (std::any_of(directionKeys.at(Direction::Down).begin(), directionKeys.at(Direction::Down).end(), sf::Keyboard::isKeyPressed))
	{
		movement.y += 1;
	}

	if (std::any_of(directionKeys.at(Direction::Left).begin(), directionKeys.at(Direction::Left).end(), sf::Keyboard::isKeyPressed))
	{
		movement.x -= 1;
	}
	
	if (std::any_of(directionKeys.at(Direction::Right).begin(), directionKeys.at(Direction::Right).end(), sf::Keyboard::isKeyPressed))
	{
		movement.x += 1;
	}

	return movement;
}
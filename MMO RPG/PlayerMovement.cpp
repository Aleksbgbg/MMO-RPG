#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(sf::Sprite& sprite, const float speed, const std::unordered_map<Character::Character::Direction, std::vector<sf::Keyboard::Key>>& directionKeys)
	:
	MovementStrategy{ sprite, speed },
	directionKeys{ directionKeys }
{
}

sf::Vector2f PlayerMovement::PickMovement(const sf::Vector2f position)
{
	sf::Vector2f movement;

	if (std::any_of(directionKeys.at(Character::Direction::Up).begin(), directionKeys.at(Character::Direction::Up).end(), sf::Keyboard::isKeyPressed))
	{
		movement.y -= 1;
	}
	
	if (std::any_of(directionKeys.at(Character::Direction::Down).begin(), directionKeys.at(Character::Direction::Down).end(), sf::Keyboard::isKeyPressed))
	{
		movement.y += 1;
	}

	if (std::any_of(directionKeys.at(Character::Direction::Left).begin(), directionKeys.at(Character::Direction::Left).end(), sf::Keyboard::isKeyPressed))
	{
		movement.x -= 1;
	}
	
	if (std::any_of(directionKeys.at(Character::Direction::Right).begin(), directionKeys.at(Character::Direction::Right).end(), sf::Keyboard::isKeyPressed))
	{
		movement.x += 1;
	}

	return movement;
}
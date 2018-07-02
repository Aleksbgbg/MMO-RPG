#pragma once

#include "MovementStrategy.h"
#include <unordered_map>
#include "Character.h"
#include <SFML/Window/Keyboard.hpp>

class PlayerMovement : public MovementStrategy
{
public:
	PlayerMovement(sf::Sprite& sprite, const float speed, const std::unordered_map<Character::Direction, std::vector<sf::Keyboard::Key>>& directionKeys);

protected:
	sf::Vector2f PickMovement(const sf::Vector2f position) override;

private:
	const std::unordered_map<Character::Direction, std::vector<sf::Keyboard::Key>>& directionKeys;
};
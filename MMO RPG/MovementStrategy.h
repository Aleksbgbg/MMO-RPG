#pragma once

#include <SFML/System/Vector2.hpp>

#include "Sprite.h"

class MovementStrategy
{
public:
	virtual ~MovementStrategy() = default;

public:
	sf::Vector2f Move();

protected:
	explicit MovementStrategy(Sprite& sprite, const float speed);

protected:
	virtual sf::Vector2f PickMovement(const sf::Vector2f position) = 0;

	void ForcePosition(const sf::Vector2f position) const;

private:
	Sprite& sprite;
	float speed;
};
#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MovementStrategy
{
public:
	virtual ~MovementStrategy() = default;

public:
	sf::Vector2f Move();

protected:
	explicit MovementStrategy(sf::Sprite& sprite, const float speed);

protected:
	virtual sf::Vector2f PickMovement(const sf::Vector2f position) = 0;

	void ForcePosition(const sf::Vector2f position) const;

private:
	sf::Sprite& sprite;
	float speed;
};
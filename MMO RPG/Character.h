#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <map>

#include "Animation.h"
#include "Graphics.h"

class Character
{
protected:
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right,
		Still
	};

public:
	void Update();
	void Draw(const Graphics& gfx) const;

	sf::Vector2f GetPosition() const;
	sf::FloatRect GetOccupation() const;

protected:
	Character(sf::Sprite sprite, const float speed);
	virtual ~Character() = default;

protected:
	virtual sf::Vector2f PickMovement() = 0;

	virtual void OnPositionUpdated(const sf::Vector2f newPosition);

protected:
	void SetPosition(const sf::Vector2f position);

protected:
	sf::Sprite sprite;
	Direction movementDirection;

	std::map<Direction, Animation> animations;

private:
	const float speed;
	sf::Vector2f lastPosition;
};
#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include <unordered_map>

#include "Animation.h"
#include "Graphics.h"
#include "MovementStrategy.h"

class Character
{
public:
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
	Character(sf::Sprite& sprite, MovementStrategy& movementStrategy);
	virtual ~Character() = default;

protected:
	virtual void OnUpdate();
	virtual void OnPositionUpdated(const sf::Vector2f newPosition);

	void SetPosition(const sf::Vector2f position);

	void ChangeMovementDirection(const Direction newDirection);

protected:
	std::unordered_map<Direction, Animation> animations;

private:
	sf::Sprite& sprite;
	Direction movementDirection;

	MovementStrategy& movementStrategy;
};
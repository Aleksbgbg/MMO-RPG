#include "Character.h"

#include "Vector.h"

#include <utility>

Character::Character(sf::Sprite sprite, const float speed)
	:
	sprite{ std::move(sprite) },
	movementDirection{ Direction::Down },
	speed{ speed }
{
}

void Character::Update()
{
	const bool wasStanding = movementDirection == Direction::Still;

	sf::Vector2f movement = PickMovement();

	if (movement.x == 0 && movement.y == 0)
	{
		if (movementDirection != Direction::Still)
		{
			animations.at(movementDirection).Stop();
		}

		movementDirection = Direction::Still;
	}
	else
	{
		normalize(movement);

		movement *= speed;

		if (wasStanding)
		{
			animations.at(movementDirection).Resume();
		}

		sprite.move(movement);

		animations.at(movementDirection).Update();
	}

	if (lastPosition != sprite.getPosition())
	{
		OnPositionUpdated(sprite.getPosition());
		lastPosition = sprite.getPosition();
	}
}

void Character::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}

sf::Vector2f Character::GetPosition() const
{
	return sprite.getPosition();
}

sf::FloatRect Character::GetOccupation() const
{
	const sf::Vector2f& spritePosition = sprite.getPosition();
	const sf::IntRect& spriteDimensions = sprite.getTextureRect();

	return sf::FloatRect{ spritePosition.x, spritePosition.y, static_cast<float>(spriteDimensions.width), static_cast<float>(spriteDimensions.height) };
}

void Character::OnPositionUpdated(const sf::Vector2f newPosition)
{
}

void Character::SetPosition(const sf::Vector2f position)
{
	sprite.setPosition(position);
	OnPositionUpdated(position);
}
#include "Character.h"

#include "Vector.h"

Character::Character(sf::Sprite& sprite, MovementStrategy& movementStrategy)
	:
	movementDirection{ Direction::Down },
	sprite{ sprite },
	movementStrategy{ movementStrategy }
{
}

void Character::Update()
{
	const bool wasStanding = movementDirection == Direction::Still;

	const sf::Vector2f movement = movementStrategy.Move();

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
		if (movement.x < 0)
		{
			movementDirection = Direction::Left;
		}
		else if (movement.x > 0)
		{
			movementDirection = Direction::Right;
		}
		else if (movement.y < 0)
		{
			movementDirection = Direction::Up;
		}
		else if (movement.y > 0)
		{
			movementDirection = Direction::Down;
		}

		if (wasStanding)
		{
			animations.at(movementDirection).Resume();
		}

		animations.at(movementDirection).Update();

		OnPositionUpdated(sprite.getPosition());
	}

	OnUpdate();
}

void Character::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}

sf::Vector2f Character::GetPosition() const
{
	const sf::FloatRect bounds = sprite.getGlobalBounds();

	return sprite.getPosition() + sf::Vector2f{ bounds.width / 2.0f, bounds.height / 2.0f };
}

sf::FloatRect Character::GetOccupation() const
{
	return sprite.getGlobalBounds();
}

void Character::OnUpdate()
{
}

void Character::OnPositionUpdated(const sf::Vector2f newPosition)
{
}

void Character::SetPosition(const sf::Vector2f position)
{
	sprite.setPosition(position);
	OnPositionUpdated(position);
}

void Character::ChangeMovementDirection(const Direction newDirection)
{
	movementDirection = newDirection;
}
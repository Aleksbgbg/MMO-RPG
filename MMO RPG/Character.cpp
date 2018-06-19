#include "Character.h"

Character::Character(const sf::Sprite& sprite)
	:
	sprite{ sprite },
	movementDirection{ Direction::Down }
{
}

void Character::Update()
{
	const bool wasStanding = movementDirection == Direction::Still;

	const sf::Vector2f movement = PickMovement();

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
		if (wasStanding)
		{
			animations.at(movementDirection).Resume();
		}

		sprite.move(movement);

		animations.at(movementDirection).Update();
	}
}

void Character::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}
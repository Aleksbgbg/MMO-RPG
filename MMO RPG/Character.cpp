#include <utility>

#include "Character.h"
#include "DeltaTime.h"

Character::Character(sf::Sprite sprite)
	:
	sprite{ std::move(sprite) },
	movementDirection{ Direction::Down }
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
		{
			const float hypotenuse = std::sqrt(movement.x * movement.x + movement.y * movement.y);

			movement.x /= hypotenuse;
			movement.y /= hypotenuse;
		}

		if (wasStanding)
		{
			animations.at(movementDirection).Resume();
		}

		sprite.move(movement);

		OnPositionUpdated(sprite.getPosition());

		animations.at(movementDirection).Update();
	}
}

void Character::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}

void Character::OnPositionUpdated(const sf::Vector2f newPosition)
{
}
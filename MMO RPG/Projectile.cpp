#include "Projectile.h"

#include "Vector.h"
#include "Rect.h"

Projectile::Projectile(const sf::Texture& texture, const sf::Vector2f sourcePosition, InteractiveCharacter* target)
	:
	sprite{ texture },
	target{ target }
{
	sprite.setScale(Scale, Scale);

	sprite.setPosition(sourcePosition);
	sprite.setOrigin(center(sprite.getLocalBounds()));
}

void Projectile::Update()
{
	const sf::Vector2f positionSprite = sprite.getPosition();
	const sf::Vector2f positionTarget = target->GetPosition();

	{
		sf::Vector2f targetVector = positionTarget - positionSprite;

		normalize(targetVector);

		targetVector *= Speed;

		sprite.move(targetVector);
	}

	static constexpr float Pi = 3.14159265359f;

	float rotationAngle = std::atan2(positionSprite.x - positionTarget.x, positionTarget.y - positionSprite.y);

	if (rotationAngle < 0.0f)
	{
		rotationAngle += 2.0f * Pi;
	}

	// Convert angle to degrees, and subtract 90 degrees due to rotation of original image
	sprite.setRotation(rotationAngle * (180.0f / Pi) - 90.0f);
}

void Projectile::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}

bool Projectile::HasReachedTarget() const
{
	return target->GetOccupation().contains(sprite.getPosition());
}

void Projectile::DealDamage() const
{
	target->TakeDamage(Damage);
}
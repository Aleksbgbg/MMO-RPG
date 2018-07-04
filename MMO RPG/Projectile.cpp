#include "Projectile.h"

#include "Vector.h"
#include "Rect.h"

Projectile::Projectile(const sf::Texture& texture, const sf::Vector2f sourcePosition, InteractiveCharacter* target)
	:
	sprite{ texture },
	target{ target }
{
	sprite.setPosition(sourcePosition);
	sprite.setOrigin(center(sprite.getLocalBounds()));
}

void Projectile::Update()
{
	const sf::Vector2f positionSprite = sprite.getPosition();
	const sf::Vector2f positionTarget = target->GetPosition();

	sf::Vector2f targetVector = positionTarget - positionSprite;

	normalize(targetVector);

	targetVector *= Speed;

	sprite.move(targetVector);

	// dot = x1*x2 + y1*y2      # dot product between [x1, y1] and [x2, y2]
	// det = x1*y2 - y1*x2      # determinant
	// angle = atan2(det, dot)  # atan2(y, x) or atan2(sin, cos)

	const float angle = std::atan2(positionSprite.x * positionTarget.y - positionSprite.y * positionTarget.x, positionSprite.x * positionTarget.x + positionSprite.y * positionTarget.y);

	sprite.setRotation(angle * 3.14159265359f / 180.0f);
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
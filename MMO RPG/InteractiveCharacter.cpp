#include "InteractiveCharacter.h"

InteractiveCharacter::InteractiveCharacter(sf::Sprite& sprite, const nlohmann::json& animationInfo, MovementStrategy& movementStrategy) 
	:
	Character{ sprite, animationInfo, movementStrategy },
	sprite{ sprite },
	health{ 100.0f },
	healthBar{ sf::Color::Green }
{
}

void InteractiveCharacter::OnDraw(const Graphics& gfx)
{
	const sf::FloatRect spriteBounds = sprite.getLocalBounds();

	healthBar.Render(gfx, health / MaxHealth, sprite.getPosition() + sf::Vector2f{ spriteBounds.width / 2.0f, -10.0f });
}

void InteractiveCharacter::TakeDamage(const float damage)
{
	health -= damage;
}
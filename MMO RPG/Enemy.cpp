#include "Enemy.h"

#include "Random.h"

using nlohmann::json;

Enemy::Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Character{ sprite, spriteConfig, movementStrategy },
	sprite{ spriteSheet },
	movementStrategy{ sprite, Random::GenerateFloat(1.0f, 2.0f), mapDimensions },
	health{ 100.0f },
	healthBar{ sf::Color::Green }
{
}

void Enemy::OnDraw(const Graphics& gfx)
{
	const sf::FloatRect spriteBounds = sprite.getLocalBounds();

	healthBar.Render(gfx, health / MaxHealth, sprite.getPosition() + sf::Vector2f{ spriteBounds.width / 2.0f, -10.0f });
}
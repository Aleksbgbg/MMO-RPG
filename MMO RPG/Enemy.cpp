#include "Enemy.h"

#include "Random.h"

using nlohmann::json;

Enemy::Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	InteractiveCharacter{ sprite, spriteConfig, movementStrategy },
	sprite{ spriteSheet },
	movementStrategy{ sprite, Random::GenerateFloat(1.0f, 2.0f), mapDimensions }
{
}
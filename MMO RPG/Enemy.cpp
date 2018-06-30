#include "Enemy.h"

using nlohmann::json;

Enemy::Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Npc{ spriteSheet, mapDimensions, spriteConfig }
{
}
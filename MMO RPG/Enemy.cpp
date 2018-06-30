#include "Enemy.h"

Enemy::Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const std::string& configFile)
	:
	Npc{ spriteSheet, mapDimensions, "Config\\" + configFile }
{
}
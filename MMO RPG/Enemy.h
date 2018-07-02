#pragma once

#include "Animation.h"
#include "Character.h"
#include "Map.h"
#include "SimpleAiMovement.h"

class Enemy : public Character
{
public:
	Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

private:
	sf::Sprite sprite;

	SimpleAiMovement movementStrategy;
};
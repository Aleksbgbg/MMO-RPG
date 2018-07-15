#pragma once

#include "Animation.h"
#include "Map.h"
#include "SimpleAiMovement.h"
#include "InteractiveCharacter.h"

class Enemy : public InteractiveCharacter
{
public:
	Enemy(const std::shared_ptr<sf::Texture>& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

private:
	Sprite sprite;
	SimpleAiMovement movementStrategy;
};
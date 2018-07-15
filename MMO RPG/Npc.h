#pragma once

#include "Animation.h"
#include "Character.h"
#include "Map.h"
#include "SimpleAiMovement.h"

class Npc : public Character
{
public:
	Npc(const std::shared_ptr<sf::Texture>& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

private:
	Sprite sprite;

	SimpleAiMovement movementStrategy;
};
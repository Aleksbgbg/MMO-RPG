#pragma once

#include "Npc.h"

class Enemy : public Npc
{
public:
	Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);
};
#pragma once

#include "Npc.h"

class Enemy : public Npc
{
public:
	explicit Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const std::string& configFile);
};
#pragma once

#include "Animation.h"
#include "Character.h"
#include "Map.h"
#include "SimpleAiMovement.h"

class Npc : public Character
{
public:
	Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

protected:
	Npc(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

private:
	Npc(sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

private:
	sf::Sprite sprite;

	SpriteInfo spriteInfo;

	SimpleAiMovement movementStrategy;
};
#include "Npc.h"

#include "Random.h"
#include "ResourceManager.h"
#include "Map.h"
#include "Json.h"

using nlohmann::json;

Npc::Npc(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const json& spriteConfig)
	:
	Character{ sprite, spriteConfig, movementStrategy },
	sprite{ spriteSheet },
	movementStrategy{ sprite, Random::GenerateFloat(1.0f, 2.0f), mapDimensions }
{
}
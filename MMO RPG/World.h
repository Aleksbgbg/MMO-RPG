#pragma once

#include <json.hpp>

#include "Npc.h"
#include "Player.h"
#include "Minimap.h"
#include "Portal.h"

class World
{
public:
	World(const std::string& mapFile, Map& map, Player& player, Minimap& minimap, nlohmann::json& worldConfig);

public:
	void Update();
	void Draw(Graphics& gfx);

	void Activate() const;

	bool PlayerCanTeleport() const;
	const Portal& FindNearestPortal() const;

	void SpawnProjectile(const Projectile& projectile);

	const Portal& GetPortal(const int index) const;

	std::shared_ptr<Character> GetCharacter(const sf::Vector2f position) const;
	bool CharacterExists(const std::shared_ptr<Character>& target) const;

private:
	sf::Vector2i dimensions;

	std::string mapFile;

	Map& map;

	Player& player;

	Minimap& minimap;

	std::vector<std::shared_ptr<Character>> characters;

	std::vector<Portal> portals;

	std::vector<Projectile> projectiles;
};
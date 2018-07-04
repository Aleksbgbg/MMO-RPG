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

	const Portal& GetPortal(const int index) const;

	Character* GetCharacter(const sf::Vector2f position) const;

private:
	sf::Vector2i dimensions;

	std::string mapFile;

	Map& map;

	Player& player;

	Minimap& minimap;

	std::vector<std::unique_ptr<Character>> characters;

	std::vector<Portal> portals;
};
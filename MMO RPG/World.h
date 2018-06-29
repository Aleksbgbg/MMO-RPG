#pragma once

#include <json.hpp>

#include <array>

#include "Npc.h"
#include "Player.h"
#include "Minimap.h"
#include "Portal.h"

class World
{
public:
	World(const std::string& mapFile, Map& map, Player& player, Camera& camera, Minimap& minimap, nlohmann::json& worldConfig);

public:
	void Update();
	void Draw(const Graphics& gfx);

	void Activate();

	bool PlayerCanTeleport() const;
	const Portal& FindNearestPortal() const;

	const Portal& GetPortal(const int index) const;

private:
	sf::Vector2i dimensions;

	std::string mapFile;

	Map& map;

	Player& player;

	Camera& camera;

	Minimap& minimap;

	std::array<std::unique_ptr<Npc>, 8> npcs;

	std::vector<Portal> portals;
};
#pragma once

#include "Camera.h"
#include "Character.h"
#include "Player.h"

class Minimap
{
public:
	Minimap(const Camera& camera, const Map& map);

public:
	void Render(Graphics& gfx, const Player& player, const std::vector<std::shared_ptr<Character>>& characters) const;
	
	void LoadNewWorld(const sf::Vector2f newWorldDimensions);

private:
	sf::Vector2f worldDimensions;

	sf::View minimapView;

	const Camera& camera;
};
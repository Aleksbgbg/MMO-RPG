#pragma once

#include "Camera.h"
#include "Character.h"

class Minimap
{
public:
	Minimap(const Camera& camera, const Map& map);

public:
	void Draw(Graphics& gfx) const;
	
	void LoadNewWorld(const sf::Vector2f newWorldDimensions);

	void AddCharacter(Character& character);

private:
	sf::Vector2f worldDimensions;

	sf::View minimapView;

	const Camera& camera;

	std::vector<Character*> characters;
};

#pragma once

#include "Camera.h"
#include "Character.h"

class Minimap
{
public:
	Minimap(const Camera& camera, const Map& map);

public:
	void Draw(Graphics& gfx) const;

	void AddCharacter(Character& character);

private:
	const sf::Vector2f worldDimensions;

	sf::View minimapView;

	const Camera& camera;

	std::vector<Character*> characters;
};

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Character.h"

class Reticle
{
public:
	Reticle();

public:
	void Update(const Character& target);
	void Draw(const Graphics& gfx) const;

private:
	sf::Sprite sprite;
};
#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Graphics.h"
#include "Character.h"

class Player : public Character
{
public:
	explicit Player(sf::Texture& spriteSheet);

protected:
	sf::Vector2f PickMovement() override;
};
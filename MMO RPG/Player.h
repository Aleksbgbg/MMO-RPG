#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Graphics.h"
#include "Character.h"

class Player : public Character
{
public:
	Player();

protected:
	sf::Vector2f PickMovement() override;

private:
	explicit Player(const sf::Texture& spriteSheet);
};
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Animation.h"
#include "Graphics.h"

class Player
{
public:
	explicit Player(Graphics& gfx);

	void Update();

private:
	sf::Texture _spriteSheet;
	sf::Sprite _sprite;

	Animation _walkAnimation;
};
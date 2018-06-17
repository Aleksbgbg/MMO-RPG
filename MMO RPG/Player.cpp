#include "Player.h"

#include <SFML/Graphics/Texture.hpp>

Player::Player(Graphics& gfx)
	:
	_sprite{ _spriteSheet },
	_walkAnimation{ _sprite, sf::Vector2i{ 91, 32 }, 3, sf::Vector2i{ 0, 0 }, 1, 0.3f }
{
	if (!_spriteSheet.loadFromFile("Player.png"))
	{
		throw std::runtime_error{ "Player spritesheet loading not successful." };
	}

	gfx.Add(_sprite);
}

void Player::Update()
{
	_walkAnimation.Update();
}
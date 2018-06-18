#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

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

	sf::Vector2f movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		movement.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		movement.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		movement.x = 1;
	}

	_sprite.move(movement);
}
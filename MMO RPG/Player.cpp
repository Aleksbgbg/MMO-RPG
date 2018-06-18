#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(Graphics& gfx)
	:
	_sprite{ _spriteSheet },
	_movementDirection{ Direction::Down }
{
	if (!_spriteSheet.loadFromFile("Player.png"))
	{
		throw std::runtime_error{ "Player spritesheet loading not successful." };
	}

	gfx.Add(_sprite);

	_animations.emplace(Direction::Up, Animation{ _sprite, sf::Vector2i{ 91, 32 }, 3, sf::Vector2i{ 0, 96 }, 1, 0.3f });
	_animations.emplace(Direction::Down, Animation{ _sprite, sf::Vector2i{ 91, 32 }, 3, sf::Vector2i{ 0, 0 }, 1, 0.3f });
	_animations.emplace(Direction::Left, Animation{ _sprite, sf::Vector2i{ 91, 32 }, 3, sf::Vector2i{ 0, 32 }, 1, 0.3f });
	_animations.emplace(Direction::Right, Animation{ _sprite, sf::Vector2i{ 91, 32 }, 3, sf::Vector2i{ 0, 64 }, 1, 0.3f });
}

void Player::Update()
{
	sf::Vector2f movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		_movementDirection = Direction::Up;
		movement.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		_movementDirection = Direction::Down;
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		_movementDirection = Direction::Left;
		movement.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		_movementDirection = Direction::Right;
		movement.x = 1;
	}

	_sprite.move(movement);
	
	_animations.at(_movementDirection).Update();
}
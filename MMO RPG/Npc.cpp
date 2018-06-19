#include "Npc.h"
#include <SFML/Window/Keyboard.hpp>
#include "Npc.h"
#include <random>

Npc::Npc(Graphics& gfx, const sf::Vector2i spriteSheetCoordinate)
	:
	_movementDirection{ Direction::Down }
{
	if (!_spriteSheet.loadFromFile("NPCs.png"))
	{
		throw std::runtime_error{ "NPC spritesheet loading not successful." };
	}

	const SpriteInfo spriteInfo{ "Npc Sprite Config.ini", _spriteSheet };

	const sf::Vector2i spritesheetDimension{ static_cast<int>(3 * spriteInfo.spriteDimension.x), static_cast<int>(4 * spriteInfo.spriteDimension.y) };

	_sprite = sf::Sprite{ _spriteSheet, sf::IntRect{ spriteSheetCoordinate.x * spritesheetDimension.x, spriteSheetCoordinate.y * spritesheetDimension.y, spritesheetDimension.x, spritesheetDimension.y } };

	{
		std::mt19937 randomEngine{ std::random_device{ }() };

		const std::uniform_int_distribution<int> xDist{ 0, Graphics::ScreenWidth - 1 };
		const std::uniform_int_distribution<int> yDist{ 0, Graphics::ScreenHeight - 1 };

		_sprite.setPosition(xDist(randomEngine), yDist(randomEngine));
	}

	_animations.emplace(Direction::Up, Animation{ _sprite, spriteInfo, spriteInfo.upRow });
	_animations.emplace(Direction::Down, Animation{ _sprite, spriteInfo, spriteInfo.downRow });
	_animations.emplace(Direction::Left, Animation{ _sprite, spriteInfo, spriteInfo.leftRow });
	_animations.emplace(Direction::Right, Animation{ _sprite, spriteInfo, spriteInfo.rightRow });

	gfx.Add(_sprite);
}
void Npc::Update()
{
	const bool wasStanding = _movementDirection == Direction::Still;

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

	if (movement.x == 0 && movement.y == 0)
	{
		if (_movementDirection != Direction::Still)
		{
			_animations.at(_movementDirection).Stop();
		}

		_movementDirection = Direction::Still;
	}
	else
	{
		if (wasStanding)
		{
			_animations.at(_movementDirection).Resume();
		}

		_sprite.move(movement);

		_animations.at(_movementDirection).Update();
	}
}
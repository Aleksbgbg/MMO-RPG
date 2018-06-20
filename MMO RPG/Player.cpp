#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "INIReader.h"

Player::Player(const sf::Texture& spriteSheet)
	:
	Character{ sf::Sprite{ spriteSheet } }
{
	const SpriteInfo spriteInfo{ "Player Sprite Config.ini", spriteSheet };

	const sf::IntRect spriteRegion = sf::IntRect{ 0, 0, static_cast<int>(spriteInfo.sheetSize.x), static_cast<int>(spriteInfo.sheetSize.y) };
	
	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

sf::Vector2f Player::PickMovement()
{
	sf::Vector2f movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		movementDirection = Direction::Up;
		movement.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		movementDirection = Direction::Down;
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		movementDirection = Direction::Left;
		movement.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		movementDirection = Direction::Right;
		movement.x = 1;
	}

	return movement;
}
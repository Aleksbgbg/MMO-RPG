#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "INIReader.h"

Player::Player()
	:
	sprite{ spriteSheet },
	movementDirection{ Direction::Down }
{
	if (!spriteSheet.loadFromFile("Player.png"))
	{
		throw std::runtime_error{ "Player spritesheet loading not successful." };
	}

	const SpriteInfo spriteInfo{ "Player Sprite Config.ini", spriteSheet };

	const sf::IntRect spriteRegion = sf::IntRect{ 0, 0, static_cast<int>(spriteInfo.sheetSize.x), static_cast<int>(spriteInfo.sheetSize.y) };
	
	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

void Player::Update()
{
	const bool wasStanding = movementDirection == Direction::Still;

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

	if (movement.x == 0 && movement.y == 0)
	{
		if (movementDirection != Direction::Still)
		{
			animations.at(movementDirection).Stop();
		}

		movementDirection = Direction::Still;
	}
	else
	{
		if (wasStanding)
		{
			animations.at(movementDirection).Resume();
		}

		sprite.move(movement);

		animations.at(movementDirection).Update();
	}
}

void Player::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}

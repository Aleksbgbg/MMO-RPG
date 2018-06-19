#include "Npc.h"

#include <SFML/Window/Keyboard.hpp>

#include <random>

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, sf::Texture& spriteSheet)
	:
	movementDirection{ Direction::Down }
{
	const SpriteInfo spriteInfo{ "Npc Sprite Config.ini", spriteSheet };

	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ spriteSheetCoordinate.x * spriteSheetDimension.x, spriteSheetCoordinate.y * spriteSheetDimension.y, spriteSheetDimension.x, spriteSheetDimension.y };

	sprite = sf::Sprite{ spriteSheet };

	{
		std::mt19937 randomEngine{ std::random_device{ }() };

		const std::uniform_int_distribution<int> xDist{ 0, Graphics::ScreenWidth - 1 };
		const std::uniform_int_distribution<int> yDist{ 0, Graphics::ScreenHeight - 1 };

		sprite.setPosition(xDist(randomEngine), yDist(randomEngine));
	}

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

void Npc::Update()
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

void Npc::Draw(const Graphics& gfx) const
{
	gfx.Draw(sprite);
}
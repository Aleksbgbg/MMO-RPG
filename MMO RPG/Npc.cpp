#include "Npc.h"

#include <SFML/Window/Keyboard.hpp>

#include "Random.h"

Npc::Npc(const sf::Vector2i spriteSheetCoordinate, sf::Texture& spriteSheet)
	:
	movementDirection{ Direction::Down }
{
	const SpriteInfo spriteInfo{ "Npc Sprite Config.ini", spriteSheet };

	const sf::Vector2i spriteSheetDimension{ static_cast<int>(spriteInfo.frameCount * spriteInfo.spriteDimension.x), static_cast<int>(SpriteInfo::RowCount * spriteInfo.spriteDimension.y) };

	const sf::IntRect spriteRegion = sf::IntRect{ spriteSheetCoordinate.x * spriteSheetDimension.x, spriteSheetCoordinate.y * spriteSheetDimension.y, spriteSheetDimension.x, spriteSheetDimension.y };

	sprite = sf::Sprite{ spriteSheet };

	sprite.setPosition(Random::Generate(0, Graphics::ScreenWidth - spriteInfo.spriteDimension.x), Random::Generate(0, Graphics::ScreenHeight - spriteInfo.spriteDimension.y));

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
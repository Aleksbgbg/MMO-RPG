#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "INIReader.h"
#include "TextureManager.h"

Player::Player(Camera& camera)
	:
	Player{ TextureManager::Get("Player2"), camera }
{
}

Player::Player(const sf::Texture& spriteSheet, Camera& camera)
	:
	Character{ sf::Sprite{ spriteSheet }, 4.0f },
	camera{ camera }
{
	UpdateCamera();

	const SpriteInfo spriteInfo{ "Player2 Sprite Config.ini", spriteSheet };

	const sf::IntRect spriteRegion = sf::IntRect{ 0, 0, static_cast<int>(spriteInfo.sheetSize.x), static_cast<int>(spriteInfo.sheetSize.y) };
	
	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });
}

sf::Vector2f Player::PickMovement()
{
	sf::Vector2f movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		movementDirection = Direction::Up;
		movement.y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		movementDirection = Direction::Down;
		movement.y = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		movementDirection = Direction::Left;
		movement.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		movementDirection = Direction::Right;
		movement.x = 1;
	}

	return movement;
}

void Player::OnPositionUpdated(const sf::Vector2f newPosition)
{
	UpdateCamera();
}

void Player::UpdateCamera() const
{
	const sf::IntRect& playerTextureRectangle = sprite.getTextureRect();

	camera.UpdatePosition(sprite.getPosition(), sf::Vector2i{ playerTextureRectangle.width, playerTextureRectangle.height });
}
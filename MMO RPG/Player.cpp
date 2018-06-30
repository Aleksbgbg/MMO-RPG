#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "INIReader.h"
#include "ResourceManager.h"
#include "Rect.h"

Player::Player(Camera& camera)
	:
	Player{ TextureManager::Get("Player2"), camera }
{
}

void Player::TeleportTo(const Portal& portal)
{
	const sf::Vector2f portalCenter = center(portal.occupation);

	const sf::FloatRect occupation = GetOccupation();

	sprite.setPosition(portalCenter - sf::Vector2f{ occupation.width / 2.0f, occupation.height / 2.0f });

	movementDirection = Direction::Down;
}

Player::Player(const sf::Texture& spriteSheet, Camera& camera)
	:
	Character{ sf::Sprite{ spriteSheet }, 4.0f },
	camera{ camera },
	lastCameraMode{ Camera::Mode::SemiFree }
{
	UpdateCamera();

	const SpriteInfo spriteInfo{ "Config\\Player2 Sprite Config.ini", spriteSheet };

	const sf::IntRect spriteRegion = sf::IntRect{ 0, 0, static_cast<int>(spriteInfo.sheetSize.x), static_cast<int>(spriteInfo.sheetSize.y) };

	animations.emplace(Direction::Up, Animation{ sprite, spriteInfo, spriteInfo.upRow, spriteRegion });
	animations.emplace(Direction::Down, Animation{ sprite, spriteInfo, spriteInfo.downRow, spriteRegion });
	animations.emplace(Direction::Left, Animation{ sprite, spriteInfo, spriteInfo.leftRow, spriteRegion });
	animations.emplace(Direction::Right, Animation{ sprite, spriteInfo, spriteInfo.rightRow, spriteRegion });

	directionKeys.emplace(Direction::Up, std::vector<sf::Keyboard::Key>{ sf::Keyboard::W });
	directionKeys.emplace(Direction::Down, std::vector<sf::Keyboard::Key>{ sf::Keyboard::S });
	directionKeys.emplace(Direction::Left, std::vector<sf::Keyboard::Key>{ sf::Keyboard::A });
	directionKeys.emplace(Direction::Right, std::vector<sf::Keyboard::Key>{ sf::Keyboard::D });
}

sf::Vector2f Player::PickMovement()
{
	sf::Vector2f movement;

	{
		const Camera::Mode cameraMode = camera.GetMode();

		if (cameraMode != lastCameraMode)
		{
			if (cameraMode == Camera::Mode::Fixed)
			{
				directionKeys.at(Direction::Up).push_back(sf::Keyboard::Up);
				directionKeys.at(Direction::Down).push_back(sf::Keyboard::Down);
				directionKeys.at(Direction::Left).push_back(sf::Keyboard::Left);
				directionKeys.at(Direction::Right).push_back(sf::Keyboard::Right);
			}
			else if (cameraMode == Camera::Mode::SemiFree)
			{
				std::vector<sf::Keyboard::Key>& upKeys = directionKeys.at(Direction::Up);
				upKeys.erase(std::remove(upKeys.begin(), upKeys.end(), sf::Keyboard::Up), upKeys.end());

				std::vector<sf::Keyboard::Key>& downKeys = directionKeys.at(Direction::Down);
				downKeys.erase(std::remove(downKeys.begin(), downKeys.end(), sf::Keyboard::Down), downKeys.end());

				std::vector<sf::Keyboard::Key>& leftKeys = directionKeys.at(Direction::Left);
				leftKeys.erase(std::remove(leftKeys.begin(), leftKeys.end(), sf::Keyboard::Left), leftKeys.end());

				std::vector<sf::Keyboard::Key>& rightKeys = directionKeys.at(Direction::Right);
				rightKeys.erase(std::remove(rightKeys.begin(), rightKeys.end(), sf::Keyboard::Right), rightKeys.end());
			}

			lastCameraMode = cameraMode;
		}
	}

	if (std::any_of(directionKeys.at(Direction::Up).begin(), directionKeys.at(Direction::Up).end(), sf::Keyboard::isKeyPressed))
	{
		movement.y = -1;
	}
	else if (std::any_of(directionKeys.at(Direction::Down).begin(), directionKeys.at(Direction::Down).end(), sf::Keyboard::isKeyPressed))
	{
		movement.y = 1;
	}

	if (std::any_of(directionKeys.at(Direction::Left).begin(), directionKeys.at(Direction::Left).end(), sf::Keyboard::isKeyPressed))
	{
		movement.x = -1;
	}
	else if (std::any_of(directionKeys.at(Direction::Right).begin(), directionKeys.at(Direction::Right).end(), sf::Keyboard::isKeyPressed))
	{
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
#include "Player.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "ResourceManager.h"
#include "Rect.h"
#include "Json.h"

Player::Player(Camera& camera)
	:
	Player{ TextureManager::Get("Player"), camera }
{
}

void Player::TeleportTo(const Portal& portal)
{
	const sf::Vector2f portalCenter = center(portal.occupation);

	const sf::FloatRect occupation = GetOccupation();

	SetPosition(portalCenter - sf::Vector2f{ occupation.width / 2.0f, occupation.height / 2.0f });

	ChangeMovementDirection(Direction::Down);
}

Player::Player(const sf::Texture& spriteSheet, Camera& camera)
	:
	Character{ sprite, read_json("Config\\Player.json"), movementStrategy },
	sprite{ spriteSheet },
	movementStrategy{ sprite, Speed, directionKeys },
	camera{ camera },
	lastCameraMode{ Camera::Mode::SemiFree }
{
	UpdateCamera();

	directionKeys.emplace(Direction::Up, std::vector<sf::Keyboard::Key>{ sf::Keyboard::W });
	directionKeys.emplace(Direction::Down, std::vector<sf::Keyboard::Key>{ sf::Keyboard::S });
	directionKeys.emplace(Direction::Left, std::vector<sf::Keyboard::Key>{ sf::Keyboard::A });
	directionKeys.emplace(Direction::Right, std::vector<sf::Keyboard::Key>{ sf::Keyboard::D });
}

void Player::OnPositionUpdated(const sf::Vector2f newPosition)
{
	UpdateCamera();
}

void Player::OnUpdate()
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

void Player::UpdateCamera() const
{
	camera.UpdatePosition(GetPosition());
}
#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Character.h"
#include "Camera.h"
#include "Portal.h"

class Player : public Character
{
public:
	explicit Player(Camera& camera);

public:
	void TeleportTo(const Portal& portal);

protected:
	sf::Vector2f PickMovement() override;

	void OnPositionUpdated(const sf::Vector2f newPosition) override;

private:
	Player(const sf::Texture& spriteSheet, Camera& camera);

private:
	void UpdateCamera() const;

private:
	Camera& camera;

	Camera::Mode lastCameraMode;

	std::map<Direction, std::vector<sf::Keyboard::Key>> directionKeys; 
};
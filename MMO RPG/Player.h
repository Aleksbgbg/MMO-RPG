#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Character.h"
#include "Camera.h"

class Player : public Character
{
public:
	explicit Player(Camera& camera);

protected:
	sf::Vector2f PickMovement() override;

	void OnPositionUpdated(const sf::Vector2f newPosition) override;

private:
	Player(const sf::Texture& spriteSheet, Camera& camera);

private:
	void UpdateCamera() const;
	static bool IsPressed(const sf::Keyboard::Key key);

private:
	Camera& camera;

	Camera::Mode lastCameraMode;

	std::map<Direction, std::vector<sf::Keyboard::Key>> directionKeys; 
};
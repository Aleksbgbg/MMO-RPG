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
	Camera& camera;
};
#pragma once

#include <unordered_map>

#include "Camera.h"
#include "Portal.h"
#include "PlayerMovement.h"
#include "Projectile.h"
#include "InteractiveCharacter.h"

class Player : public InteractiveCharacter
{
public:
	explicit Player(Camera& camera);

public:
	void TeleportTo(const Portal& portal);
	void ForcePosition(const sf::FloatRect rectangle);

	bool IsWithinRange(const InteractiveCharacter& character) const;

protected:
	void OnPositionUpdated(const sf::Vector2f newPosition) override;
	void OnUpdate() override;

private:
	Player(const sf::Texture& spriteSheet, Camera& camera);

private:
	void UpdateCamera() const;

private:
	static constexpr float AttackRadius = 400.0f;
	static constexpr float AttackArea = AttackRadius * AttackRadius;

	static constexpr float Speed = 4.0f;

private:
	sf::Sprite sprite;

	PlayerMovement movementStrategy;

	Camera& camera;

	Camera::Mode lastCameraMode;

	std::unordered_map<Direction, std::vector<sf::Keyboard::Key>> directionKeys; 
};
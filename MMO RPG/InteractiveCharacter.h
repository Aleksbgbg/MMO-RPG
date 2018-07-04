#pragma once

#include "Character.h"
#include "StatBar.h"

class InteractiveCharacter : public Character
{
public:
	InteractiveCharacter(sf::Sprite& sprite, const nlohmann::json& animationInfo, MovementStrategy& movementStrategy);

public:
	void OnDraw(const Graphics& gfx) override;

private:
	static constexpr float MaxHealth = 100.0f;

private:
	sf::Sprite& sprite;

	float health;
	StatBar healthBar;
};
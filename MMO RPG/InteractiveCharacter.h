#pragma once

#include "Character.h"
#include "StatBar.h"

class InteractiveCharacter : public Character
{
public:
	InteractiveCharacter(Sprite& sprite, const nlohmann::json& animationInfo, MovementStrategy& movementStrategy);

public:
	void OnDraw(const Graphics& gfx) override;

	void TakeDamage(const float damage);

	bool IsAlive() const;

private:
	static constexpr float MaxHealth = 100.0f;

private:
	Sprite& sprite;

	float health;
	StatBar healthBar;
};
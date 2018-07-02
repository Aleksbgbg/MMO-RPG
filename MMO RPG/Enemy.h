#pragma once

#include "Animation.h"
#include "Character.h"
#include "Map.h"
#include "SimpleAiMovement.h"
#include "StatBar.h"

class Enemy : public Character
{
public:
	Enemy(const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions, const nlohmann::json& spriteConfig);

protected:
	void OnDraw(const Graphics& gfx) override;

private:
	static constexpr float MaxHealth = 100.0f;

private:
	sf::Sprite sprite;
	SimpleAiMovement movementStrategy;

	float health;
	StatBar healthBar;
};
#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Graphics.h"
#include "InteractiveCharacter.h"

class Projectile
{
public:
	Projectile(const sf::Texture& texture, const sf::Vector2f sourcePosition, InteractiveCharacter* target);

public:
	void Update();
	void Draw(const Graphics& gfx) const;

	bool HasReachedTarget() const;

	void DealDamage() const;

private:
	static constexpr float Speed = 10.0f;
	static constexpr float Damage = 10.0f;

private:
	sf::Sprite sprite;

	InteractiveCharacter* target;
};
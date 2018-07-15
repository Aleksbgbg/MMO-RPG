#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Graphics.h"
#include "InteractiveCharacter.h"

class Projectile
{
public:
	Projectile(const std::shared_ptr<sf::Texture>& texture, const sf::Vector2f sourcePosition, const std::shared_ptr<InteractiveCharacter> target);

public:
	void Update();
	void Draw(const Graphics& gfx) const;

	bool HasReachedTarget() const;

	void DealDamage() const;

private:
	static constexpr float Scale = 0.5f;

	static constexpr float Speed = 10.0f;
	static constexpr float Damage = 10.0f;

private:
	Sprite sprite;

	std::shared_ptr<InteractiveCharacter> target;
};
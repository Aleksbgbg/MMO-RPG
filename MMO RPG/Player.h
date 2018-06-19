#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>

#include "Animation.h"
#include "Graphics.h"

class Player
{
public:
	Player();

	void Update();
	void Draw(const Graphics& gfx) const;

private:
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right,
		Still
	};

private:
	sf::Texture spriteSheet;
	sf::Sprite sprite;

	Direction movementDirection;

	std::map<Direction, Animation> animations;
};
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>

#include "Animation.h"
#include "Graphics.h"

class Player
{
public:
	explicit Player(Graphics& gfx);

	void Update();

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
	sf::Texture _spriteSheet;
	sf::Sprite _sprite;

	Direction _movementDirection;

	std::map<Direction, Animation> _animations;
};
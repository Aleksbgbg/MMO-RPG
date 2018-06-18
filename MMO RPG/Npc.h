#pragma once

#include <map>

#include "Animation.h"
#include "Graphics.h"

class Npc
{
public:
	explicit Npc(Graphics& gfx, sf::Vector2i spriteSheetCoordinate);

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
	sf::Sprite _sprite;
	sf::Texture _spriteSheet;

	Direction _movementDirection;

	std::map<Direction, Animation> _animations;
};
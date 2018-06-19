#pragma once

#include <map>

#include "Animation.h"
#include "Graphics.h"

class Npc
{
public:
	explicit Npc(sf::Vector2i spriteSheetCoordinate);

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
	sf::Sprite sprite;
	sf::Texture spriteSheet;

	Direction movementDirection;

	std::map<Direction, Animation> animations;
};
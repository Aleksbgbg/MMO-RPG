#pragma once

#include <map>

#include "Animation.h"
#include "Graphics.h"

class Npc
{
public:
	Npc(sf::Vector2i spriteSheetCoordinate, sf::Texture& spriteSheet);

	void Update();

	void Draw(const Graphics& gfx) const;

private:
	void GenerateTargetPosition();

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
	SpriteInfo spriteInfo;

	std::map<Direction, Animation> animations;

	Direction movementDirection;

	sf::Vector2f targetPosition;
};
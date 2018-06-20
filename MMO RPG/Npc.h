#pragma once

#include "Animation.h"
#include "Graphics.h"
#include "Character.h"

class Npc : public Character
{
public:
	Npc(sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet);

protected:
	 sf::Vector2f PickMovement() override;

private:
	void GenerateTargetPosition();

private:
	SpriteInfo spriteInfo;

	sf::Vector2i targetPosition;
};
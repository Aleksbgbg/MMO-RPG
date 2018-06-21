#pragma once

#include "Animation.h"
#include "Graphics.h"
#include "Character.h"

class Npc : public Character
{
public:
	explicit Npc(const sf::Vector2i spriteSheetCoordinate);

protected:
	 sf::Vector2f PickMovement() override;
	 
	 void OnPositionUpdated(const sf::Vector2f newPosition) override;

private:
	Npc(sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet);

private:
	void GenerateTargetPosition();

private:
	SpriteInfo spriteInfo;

	sf::Vector2i targetPosition;

	sf::Vector2i startingTargetVector;
};
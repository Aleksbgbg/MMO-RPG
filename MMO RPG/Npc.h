#pragma once

#include "Animation.h"
#include "Character.h"
#include "Map.h"

class Npc : public Character
{
public:
	Npc(const sf::Vector2i spriteSheetCoordinate, const sf::Vector2i mapDimensions);

protected:
	 sf::Vector2f PickMovement() override;
	 
	 void OnPositionUpdated(const sf::Vector2f newPosition) override;

private:
	Npc(sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet, const sf::Vector2i mapDimensions);

private:
	void GenerateTargetPosition();

private:
	const sf::Vector2i mapDimensions;

	SpriteInfo spriteInfo;

	sf::Vector2f targetPosition;

	sf::Vector2f startingTargetVector;
};
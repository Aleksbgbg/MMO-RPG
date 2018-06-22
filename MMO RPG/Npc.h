#pragma once

#include "Animation.h"
#include "Graphics.h"
#include "Character.h"

class Npc : public Character
{
public:
	Npc(const sf::Vector2i spriteSheetCoordinate, const Map& map);

protected:
	 sf::Vector2f PickMovement() override;
	 
	 void OnPositionUpdated(const sf::Vector2f newPosition) override;

private:
	Npc(sf::Vector2i spriteSheetCoordinate, const sf::Texture& spriteSheet, const Map& map);

private:
	void GenerateTargetPosition();

private:
	const Map& map;

	SpriteInfo spriteInfo;

	sf::Vector2f targetPosition;

	sf::Vector2f startingTargetVector;
};
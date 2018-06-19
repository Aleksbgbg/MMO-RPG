#pragma once

#include "SpriteInfo.h"

#include <SFML/Graphics/Sprite.hpp>

class Animation
{
public:
	Animation(sf::Sprite& sprite, const SpriteInfo& spriteInfo, const int sheetRow);

public:
	void SwitchFrame(const int frame) const;

	void Resume();
	void Stop();	

	void Update();

private:
	void NextFrame();

private:
	sf::Sprite& sprite;

	const sf::Vector2i frameSize;
	const sf::Vector2i startingPosition;

	const float frameTime;
	float currentFrameRunningTime;

	const int frameCount;
	const int defaultFrame;
	int currentFrame;

	bool isStopped;
};
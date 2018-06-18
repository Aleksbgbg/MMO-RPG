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
	sf::Sprite& _sprite;

	const sf::Vector2i _frameSize;
	const sf::Vector2i _startingPosition;

	const float _frameTime;
	float _currentFrameRunningTime;

	const int _frameCount;
	const int _defaultFrame;
	int _currentFrame;

	bool _isStopped;
};